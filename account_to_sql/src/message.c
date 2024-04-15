#include "account.h"
#include "read_message.h"
#include "value_validator.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_TAG "NA"
#define BALANCE_TAG "AB"
#define LEDGER_TAG "LB"
#define UPDATE_TIME_TAG "UT"

static int ReadAccountRecord(FILE* input,
                             const struct ValueValidator* validator,
                             struct AccountRecord* account_record);
static int ReadTag(FILE* input, char* tag);
static int ReadLength(FILE* input, uint32_t* length);
static int ReadValue(FILE* input, uint32_t length, char* value);
static int ReadLengthValue(FILE* input, uint32_t max_length, uint32_t* length,
                           char* value);
static int ReadAccountNumber(FILE* input, struct AccountNumber* account_number);
static int ReadAccountBalance(FILE* input,
                              struct AccountBalance* account_balance);
static int ReadLedgerBalance(FILE* input,
                             struct AccountLedgerBalance* ledger_balance);
static int ReadUpdateTime(FILE* input, struct AccountUpdateTime* update_time);
static char PeakChar(FILE* input);

int ReadAccountRecords(FILE* input, struct AccountRecords* account_records) {
  int err = 0;

  const struct ValueValidator validator = NewValueValidator();

  while (!err && !feof(input)) {
    struct AccountRecord account_record;
    err = ReadAccountRecord(input, &validator, &account_record);

    if (!err) {
      AppendAccountRecord(account_records, &account_record);
    }
  }

  return err;
}

static int ReadAccountRecord(FILE* input,
                             const struct ValueValidator* validator,
                             struct AccountRecord* account_record) {
  *account_record = (struct AccountRecord){
      .number = {.length = 0},
      .balance = {.length = 0},
      .ledger_balance = {.length = 0},
      .update_time = {.length = 0},
  };

  int err = 0;

  char c;

  do {
    c = fgetc(input);
  } while (c != EOF && isspace(c));

  if (c == EOF) {
    err = 1;
    goto cleanup;
  }

  if (ungetc(c, input) == EOF) {
    err = 1;
    goto cleanup;
  }

  char tag[TAG_LENGTH];

  while (!feof(input) && !isspace(PeakChar(input))) {
    if (ReadTag(input, tag) != 0) {
      err = 1;
      goto cleanup;
    }

    if (strncmp(tag, NUMBER_TAG, TAG_LENGTH) == 0 &&
        account_record->number.length == 0) {
      err = ReadAccountNumber(input, &account_record->number) != 0 ||
            !validator->number(account_record->number.value);

    } else if (strncmp(tag, BALANCE_TAG, TAG_LENGTH) == 0 &&
               account_record->balance.length == 0) {
      err = ReadAccountBalance(input, &account_record->balance) != 0 ||
            !validator->balance(account_record->balance.value);

    } else if (strncmp(tag, LEDGER_TAG, TAG_LENGTH) == 0 &&
               account_record->ledger_balance.length == 0) {
      err = ReadLedgerBalance(input, &account_record->ledger_balance) != 0 ||
            !validator->ledger_balance(account_record->ledger_balance.value);

    } else if (strncmp(tag, UPDATE_TIME_TAG, TAG_LENGTH) == 0 &&
               account_record->update_time.length == 0) {
      err = ReadUpdateTime(input, &account_record->update_time) != 0 ||
            !validator->update_time(account_record->update_time.value);
    } else {
      err = 1;
    }

    if (err) {
      goto cleanup;
    }
  }

  err = account_record->balance.length == 0 ||
        account_record->number.length == 0 ||
        account_record->update_time.length == 0;

  if (!err) {
    while (isspace(PeakChar(input))) {
      fgetc(input);
    }
  }

cleanup:
  return err;
}

static int ReadTag(FILE* input, char* tag) {
  return fread(tag, sizeof(char), TAG_LENGTH, input) != TAG_LENGTH;
}

static int ReadLength(FILE* input, uint32_t* length) {
  int err = 0;

  char length_str[LENGTH_LENGTH + 1];
  err = fread(length_str, sizeof(char), LENGTH_LENGTH, input) != LENGTH_LENGTH;
  length_str[LENGTH_LENGTH] = 0;

  if (!err) {
    err = sscanf(length_str, "%u", length) != 1;
  }

  return err;
}

static int ReadValue(FILE* input, uint32_t length, char* value) {
  value[length] = 0;
  return fread(value, sizeof(char), length, input) != length;
}

static int ReadLengthValue(FILE* input, uint32_t max_length, uint32_t* length,
                           char* value) {
  int err = 0;

  err = ReadLength(input, length);

  if (!err) {
    err = *length > max_length;
  }

  if (!err) {
    err = ReadValue(input, *length, value);
  }

  return err;
}

static int ReadAccountNumber(FILE* input,
                             struct AccountNumber* account_number) {
  return ReadLengthValue(input, ACCOUNT_NUMBER_LENGTH, &account_number->length,
                         account_number->value);
}

static int ReadAccountBalance(FILE* input,
                              struct AccountBalance* account_balance) {
  return ReadLengthValue(input, ACCOUNT_BALANCE_LENGTH,
                         &account_balance->length, account_balance->value);
}

static int ReadLedgerBalance(FILE* input,
                             struct AccountLedgerBalance* ledger_balance) {
  return ReadLengthValue(input, ACCOUNT_LEDGER_LENGTH, &ledger_balance->length,
                         ledger_balance->value);
}

static int ReadUpdateTime(FILE* input, struct AccountUpdateTime* update_time) {
  return ReadLengthValue(input, ACCOUNT_UPDATE_TIME_LENGTH,
                         &update_time->length, update_time->value);
}

static char PeakChar(FILE* input) {
  char c;

  c = fgetc(input);
  ungetc(c, input);

  return c;
}

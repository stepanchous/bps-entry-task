#include "account_deserialization.h"

#include <string.h>

#include "account_message.h"
#include "deserialization.h"
#include "value_validation.h"

int DeserializeAccount(const struct DataMessage* message,
                       struct Account* account) {
  int err = 0;

  *account = (struct Account){
      .number = "",
      .balance = 0,
      .optional_ledger_balance =
          {
              .has_value = false,
              .ledger_balance = 0,
          },
      .update_date = 0,
      .update_time = 0,
  };

  bool has_number = false;
  bool has_balance = false;
  bool has_ledger_balance = false;
  bool has_update_time = false;

  for (uint32_t i = 0; i < message->size; ++i) {
    if (strncmp(message->data[i].tag, ACCOUNT_NUMBER_TAG, TAG_LENGTH) == 0 &&
        !has_number &&
        IsAlphaNumeric(message->data[i].value, ACCOUNT_NUMBER_LENGTH)) {
      DeserializeString(message->data[i].value, account->number);
      has_number = true;

    } else if (strncmp(message->data[i].tag, ACCOUNT_BALANCE_TAG, TAG_LENGTH) ==
                   0 &&
               !has_balance &&
               IsSignedNumeric(message->data[i].value,
                               ACCOUNT_BALANCE_LENGTH)) {
      account->balance = DeserializeSignedInteger(message->data[i].value);
      has_balance = true;

    } else if (strncmp(message->data[i].tag, ACCOUNT_LEDGER_BALANCE_TAG,
                       TAG_LENGTH) == 0 &&
               !has_ledger_balance &&
               IsSignedNumeric(message->data[i].value,
                               ACCOUNT_LEDGER_BALANCE_LENGTH)) {
      account->optional_ledger_balance.ledger_balance =
          DeserializeSignedInteger(message->data[i].value);
      account->optional_ledger_balance.has_value = true;

      has_ledger_balance = true;

    } else if (strncmp(message->data[i].tag, ACCOUNT_UPDATE_TIME_TAG,
                       TAG_LENGTH) == 0 &&
               !has_update_time &&
               IsDateTime(message->data[i].value, ACCOUNT_UPDATE_TIME_LENGTH)) {
      struct DateTime datetime = DeserializeDateTime(message->data[i].value);

      account->update_date = datetime.date;
      account->update_time = datetime.time;

      has_update_time = true;
    } else {
      err = 1;
    }
  }

  if (!err) {
    err = !has_number || !has_balance || !has_update_time;
  }

  return err;
}

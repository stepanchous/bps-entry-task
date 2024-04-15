#ifndef BSP_ACCOUNT_H
#define BSP_ACCOUNT_H

#include <stdint.h>

#define ACCOUNT_NUMBER_LENGTH 24
#define ACCOUNT_BALANCE_LENGTH 13
#define ACCOUNT_LEDGER_LENGTH 13
#define ACCOUNT_UPDATE_TIME_LENGTH 19
#define TAG_LENGTH 2
#define LENGTH_LENGTH 2

struct AccountNumber {
  uint32_t length;
  char value[ACCOUNT_NUMBER_LENGTH + 1];
};

struct AccountBalance {
  uint32_t length;
  char value[ACCOUNT_BALANCE_LENGTH + 1];
};

struct AccountLedgerBalance {
  uint32_t length;
  char value[ACCOUNT_LEDGER_LENGTH + 1];
};

struct AccountUpdateTime {
  uint32_t length;
  char value[ACCOUNT_UPDATE_TIME_LENGTH + 1];
};

struct AccountRecord {
  struct AccountNumber number;
  struct AccountBalance balance;
  struct AccountLedgerBalance ledger_balance;
  struct AccountUpdateTime update_time;
};

struct AccountRecords {
  struct AccountRecord* data;
  uint32_t size;
  uint32_t capacity_;
};

struct AccountRecords NewAccountRecords(void);

void AppendAccountRecord(struct AccountRecords* records,
                         const struct AccountRecord* record);

void DeleteAccountRecords(struct AccountRecords* account_records);

#endif  // !BSP_ACCOUNT_H

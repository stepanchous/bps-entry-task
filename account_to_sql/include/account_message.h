#ifndef BPS_ACCOUNT_MESSAGE_H
#define BPS_ACCOUNT_MESSAGE_H

#include <stdint.h>

#define ACCOUNT_NUMBER_LENGTH 24
#define ACCOUNT_BALANCE_LENGTH 13
#define ACCOUNT_LEDGER_LENGTH 13
#define ACCOUNT_UPDATE_TIME_LENGTH 19
#define TAG_LENGTH 2
#define LENGTH_LENGTH 2

struct AccountNumberMessage {
  uint32_t length;
  char value[ACCOUNT_NUMBER_LENGTH + 1];
};

struct AccountBalanceMessage {
  uint32_t length;
  char value[ACCOUNT_BALANCE_LENGTH + 1];
};

struct AccountLedgerBalanceMessage {
  uint32_t length;
  char value[ACCOUNT_LEDGER_LENGTH + 1];
};

struct AccountUpdateTimeMessage {
  uint32_t length;
  char value[ACCOUNT_UPDATE_TIME_LENGTH + 1];
};

struct AccountMessage {
  struct AccountNumberMessage number;
  struct AccountBalanceMessage balance;
  struct AccountLedgerBalanceMessage ledger_balance;
  struct AccountUpdateTimeMessage update_time;
};

struct AccountMessages {
  struct AccountMessage* data;
  uint32_t size;
  uint32_t capacity_;
};

struct AccountMessages NewAccountMessages(void);

void AppendAccountMessage(struct AccountMessages* records,
                          const struct AccountMessage* record);

void DeleteAccountMessages(struct AccountMessages* account_records);

#endif  // !BPS_ACCOUNT_MESSAGE_H

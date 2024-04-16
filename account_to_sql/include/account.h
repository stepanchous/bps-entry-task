#ifndef BPS_ACCOUNT_H
#define BPS_ACCOUNT_H

#include <stdbool.h>
#include <stdint.h>

#define ACCOUNT_NUMBER_LENGTH 24

struct Account {
  char number[ACCOUNT_NUMBER_LENGTH + 1];
  int64_t balance;
  struct {
    bool has_value;
    int64_t ledger_balance;
  } optional_ledger_balance;
  uint64_t update_date;
  uint32_t update_time;
};

struct Accounts {
  struct Account* data;
  uint32_t size;
  uint32_t capacity_;
};

struct Accounts NewAccounts(void);
void AppendAccount(struct Accounts* accounts, const struct Account* account);
void DeleteAccounts(struct Accounts* accounts);

#endif  // !BPS_ACCOUNT_H

#ifndef BPS_ACCOUNT_H
#define BPS_ACCOUNT_H

#include <stdbool.h>
#include <stdint.h>

#define ACCOUNT_NUMBER_LENGTH 24

struct Account {
  char number[ACCOUNT_NUMBER_LENGTH + 1];
  uint64_t balance;
  struct {
    bool has_value;
    uint64_t ledger_balance;
  };
  uint64_t update_date;
  uint32_t update_time;
};

#endif  // !BPS_ACCOUNT_H

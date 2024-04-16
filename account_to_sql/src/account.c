#include "account.h"

#include <stdlib.h>
#include <string.h>

bool IsEqualAccount(const struct Account* lhs, const struct Account* rhs) {
  return strcmp(lhs->number, rhs->number) == 0 &&
         lhs->balance == rhs->balance &&
         lhs->optional_ledger_balance.has_value ==
             rhs->optional_ledger_balance.has_value &&
         lhs->optional_ledger_balance.ledger_balance ==
             rhs->optional_ledger_balance.ledger_balance &&
         lhs->update_date == rhs->update_date &&
         lhs->update_time == rhs->update_time;
}

struct Accounts NewAccounts(void) {
  return (struct Accounts){
      .data = NULL,
      .size = 0,
      .capacity_ = 0,
  };
}

void AppendAccount(struct Accounts* accounts, const struct Account* account) {
  if (accounts->size == accounts->capacity_) {
    uint32_t new_capacity =
        accounts->capacity_ == 0 ? 1 : 2 * accounts->capacity_;

    accounts->data =
        realloc(accounts->data, new_capacity * sizeof(struct Account));
    accounts->capacity_ = new_capacity;
  }

  accounts->data[accounts->size] = *account;

  ++accounts->size;
}

void DeleteAccounts(struct Accounts* accounts) {
  free(accounts->data);

  accounts->data = NULL;
  accounts->size = 0;
  accounts->capacity_ = 0;
}

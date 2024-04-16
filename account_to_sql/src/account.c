#include "account.h"

#include <stdlib.h>

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

#include "account_message.h"

#include <stdlib.h>

struct AccountMessages NewAccountMessages(void) {
  return (struct AccountMessages){
      .data = NULL,
      .size = 0,
      .capacity_ = 0,
  };
}

void AppendAccountMessage(struct AccountMessages* records,
                          const struct AccountMessage* record) {
  if (records->size == records->capacity_) {
    uint32_t new_capacity =
        records->capacity_ == 0 ? 1 : 2 * records->capacity_;

    records->data =
        realloc(records->data, new_capacity * sizeof(struct AccountMessage));
    records->capacity_ = new_capacity;
  }

  records->data[records->size] = *record;

  ++records->size;
}

void DeleteAccountMessages(struct AccountMessages* account_records) {
  free(account_records->data);
}

#include "account.h"

#include <stdlib.h>

struct AccountRecords NewAccountRecords(void) {
  return (struct AccountRecords){
      .data = NULL,
      .size = 0,
      .capacity_ = 0,
  };
}

void AppendAccountRecord(struct AccountRecords* records,
                         const struct AccountRecord* record) {
  if (records->size == records->capacity_) {
    uint32_t new_capacity =
        records->capacity_ == 0 ? 1 : 2 * records->capacity_;

    records->data =
        realloc(records->data, new_capacity * sizeof(struct AccountRecord));
    records->capacity_ = new_capacity;
  }

  records->data[records->size] = *record;

  ++records->size;
}

void DeleteAccountRecords(struct AccountRecords* account_records) {
  free(account_records->data);
}

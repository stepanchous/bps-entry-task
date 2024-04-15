#ifndef BPS_VALUE_VALIDATOR_H
#define BPS_VALUE_VALIDATOR_H

#include <stdbool.h>

struct ValueValidator {
  bool (*number)(const char*);
  bool (*balance)(const char*);
  bool (*ledger_balance)(const char*);
  bool (*update_time)(const char*);
};

struct ValueValidator NewValueValidator(void);

#endif  // !BPS_VALUE_VALIDATOR_H

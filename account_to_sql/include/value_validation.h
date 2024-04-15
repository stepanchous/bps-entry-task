#ifndef BPS_VALUE_VALIDATOR_H
#define BPS_VALUE_VALIDATOR_H

#include <stdbool.h>

bool MatchNumber(const char* number);
bool MatchBalance(const char* balance);
bool MatchLedgerBalance(const char* ledger_balance);
bool MatchUpdateTime(const char* update_time);

#endif  // !BPS_VALUE_VALIDATOR_H

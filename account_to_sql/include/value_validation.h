#ifndef BPS_VALUE_VALIDATOR_H
#define BPS_VALUE_VALIDATOR_H

#include <stdbool.h>
#include <stdint.h>

bool IsNumeric(const char* s, uint32_t max_length);
bool IsSignedNumeric(const char* s, uint32_t max_length);
bool IsAlphaNumeric(const char* s, uint32_t max_length);
bool IsDateTime(const char* s, uint32_t max_length);

#endif  // !BPS_VALUE_VALIDATOR_H

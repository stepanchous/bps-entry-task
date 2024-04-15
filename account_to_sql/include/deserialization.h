#ifndef BPS_DESERIALIZATION_H
#define BPS_DESERIALIZATION_H

#include <stdint.h>

struct DateTime {
  uint64_t date;
  uint32_t time;
};

void DeserializeString(const char* src, char* dst);
int64_t DeserializeSignedInteger(const char* s);
struct DateTime DeserializeDateTime(const char* s);

#endif  // !BPS_DESERIALIZATION_H

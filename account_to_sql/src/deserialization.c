#include "deserialization.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

void DeserializeString(const char* src, char* dst) { strcpy(dst, src); }

int64_t DeserializeSignedInteger(const char* s) {
  int64_t value;

  sscanf(s + 1, "%ld", &value);

  value = s[0] == 'D' ? -value : value;

  return value;
}

struct DateTime DeserializeDateTime(const char* s) {
  struct tm ti = {0};

  strptime(s, "%Y-%m-%d %H:%M:%S", &ti);

  ti.tm_year += 1900;
  ti.tm_mon += 1;

  return (struct DateTime){
      .date = 10000lu * (uint64_t)ti.tm_year + 100lu * (uint64_t)ti.tm_mon +
              (uint64_t)ti.tm_mday,
      .time = (uint32_t)10000u * ti.tm_hour + 100u * ti.tm_min + ti.tm_sec,
  };
}

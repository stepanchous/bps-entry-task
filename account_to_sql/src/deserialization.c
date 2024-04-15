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

  struct tm ti_copy = ti;

  ti.tm_hour = ti.tm_min = ti.tm_sec = 0;

  time_t date = mktime(&ti);
  time_t stamp = mktime(&ti_copy);

  return (struct DateTime){
      .date = (uint64_t)(mktime(&ti)),
      .time = (uint32_t)(difftime(stamp, date)),
  };
}

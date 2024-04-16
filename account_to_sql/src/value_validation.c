#include "value_validation.h"

#include <ctype.h>
#include <string.h>
#include <time.h>

bool IsNumeric(const char* s, uint32_t max_length) {
  uint32_t length = strlen(s);

  if (length == 0 || length > max_length) {
    return false;
  }

  bool is_valid = true;

  for (const char* c = s; *c != '\0' && is_valid; ++c) {
    is_valid = '0' <= *c && *c <= '9';
  }

  return is_valid;
}

bool IsSignedNumeric(const char* s, uint32_t max_length) {
  uint32_t length = strlen(s);

  if (length == 0 || length > max_length) {
    return false;
  }

  bool is_valid = *s == 'C' || *s == 'D';

  ++s;

  return is_valid && IsNumeric(s, max_length - 1);
}

bool IsAlphaNumeric(const char* s, uint32_t max_length) {
  uint32_t length = strlen(s);

  if (length == 0 || length > max_length) {
    return false;
  }

  bool is_valid = true;

  for (const char* c = s; *c != '\0' && is_valid; ++c) {
    is_valid = isalnum(*c);
  }

  return is_valid;
}

bool IsDateTime(const char* update_time, uint32_t max_length) {
  if (strlen(update_time) > max_length) {
    return false;
  }

  struct tm ti = {0};

  char* last_proccessed = strptime(update_time, "%Y-%m-%d %H:%M:%S", &ti);

  bool is_valid = strlen(update_time) == 19 &&
                  (last_proccessed != NULL && *last_proccessed == '\0');

  if (is_valid) {
    struct tm ti_copy = ti;
    mktime(&ti);

    is_valid = ti_copy.tm_year == ti.tm_year && ti_copy.tm_mon == ti.tm_mon &&
               ti_copy.tm_mday == ti.tm_mday && ti_copy.tm_hour == ti.tm_hour &&
               ti_copy.tm_min == ti.tm_min && ti_copy.tm_sec == ti.tm_sec;
  }

  return is_valid;
}

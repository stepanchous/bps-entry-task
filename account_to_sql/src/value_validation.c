#include "value_validation.h"

#define _XOPEN_SOURCE
#include <string.h>
#include <time.h>

static bool IsNumeric(const char* s);
static bool IsSignedNumeric(const char* s);

bool MatchNumber(const char* number) { return IsNumeric(number); }

bool MatchBalance(const char* balance) { return IsSignedNumeric(balance); }

bool MatchLedgerBalance(const char* ledger_balance) {
  return IsSignedNumeric(ledger_balance);
}

bool MatchUpdateTime(const char* update_time) {
  struct tm ti;

  char* last_proccessed = strptime(update_time, "%Y-%m-%d %H:%M:%S", &ti);

  bool is_valid = strlen(update_time) == 19 && *last_proccessed == '\0';

  if (is_valid) {
    struct tm ti_copy = ti;
    mktime(&ti);

    is_valid = ti_copy.tm_year == ti.tm_year && ti_copy.tm_mon == ti.tm_mon &&
               ti_copy.tm_mday == ti.tm_mday && ti_copy.tm_hour == ti.tm_hour &&
               ti_copy.tm_min == ti.tm_min && ti_copy.tm_sec == ti.tm_sec;
  }

  return is_valid;
}

static bool IsNumeric(const char* s) {
  if (*s == '\0') {
    return false;
  }

  bool is_valid = true;

  for (const char* c = s; *c != '\0' && is_valid; ++c) {
    is_valid = '0' <= *c && *c <= '9';
  }

  return is_valid;
}
static bool IsSignedNumeric(const char* s) {
  if (*s == '\0') {
    return false;
  }

  bool is_valid = *s == 'C' || *s == 'D';

  ++s;

  return is_valid && IsNumeric(s);
}

#include "test.h"

#include <check.h>

#include "deserialization.h"

START_TEST(DeserializeStringEmpty) {
  char src[] = "";
  char dst[16];

  DeserializeString(src, dst);

  ck_assert_str_eq(src, dst);
}

START_TEST(DeserializeStringValid) {
  char src[] = "hello123";
  char dst[16];

  DeserializeString(src, dst);

  ck_assert_str_eq(src, dst);
}

START_TEST(DeserializeSignedIntegerPositive) {
  char s[] = "C000123";

  int64_t res = DeserializeSignedInteger(s);

  ck_assert_int_eq(res, 123);
}

START_TEST(DeserializeSignedIntegerNegative) {
  char s[] = "D123";

  int64_t res = DeserializeSignedInteger(s);

  ck_assert_int_eq(res, -123);
}

START_TEST(DeserializeDateCurrent) {
  char s[] = "2024-04-16 03:05:00";

  struct DateTime date_time = DeserializeDateTime(s);

  ck_assert_int_eq(date_time.time, 30500);
  ck_assert_int_eq(date_time.date, 20240416);
}

START_TEST(DeserializePast) {
  char s[] = "2000-01-01 00:00:00";

  struct DateTime date_time = DeserializeDateTime(s);

  ck_assert_int_eq(date_time.time, 0);
  ck_assert_int_eq(date_time.date, 20000101);
}

Suite* DeserializationSuite(void) {
  Suite* suite;
  TCase* tc_core;

  suite = suite_create("AccountsTests");
  tc_core = tcase_create("AccountsTestsCore");

  tcase_add_test(tc_core, DeserializeStringEmpty);
  tcase_add_test(tc_core, DeserializeStringValid);
  tcase_add_test(tc_core, DeserializeSignedIntegerPositive);
  tcase_add_test(tc_core, DeserializeSignedIntegerNegative);
  tcase_add_test(tc_core, DeserializeDateCurrent);
  tcase_add_test(tc_core, DeserializePast);

  suite_add_tcase(suite, tc_core);

  return suite;
}

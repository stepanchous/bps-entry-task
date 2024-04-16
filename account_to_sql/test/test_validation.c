#include "test.h"

#include <check.h>

#include "value_validation.h"

START_TEST(IsNumericEmpty) {
  char s[] = "";

  ck_assert(!IsNumeric(s, 2));
}
END_TEST

START_TEST(IsNumericGreaterSize) {
  char s[] = "1234";

  ck_assert(!IsNumeric(s, 2));
}
END_TEST

START_TEST(IsNumericInvalidContent) {
  char s[] = "12a2";

  ck_assert(!IsNumeric(s, 4));
}
END_TEST

START_TEST(IsNumericValidLessSize) {
  char s[] = "122";

  ck_assert(IsNumeric(s, 4));
}
END_TEST

START_TEST(IsNumericValidEqualSize) {
  char s[] = "0122";

  ck_assert(IsNumeric(s, 4));
}
END_TEST

START_TEST(IsAlphaNumericEmpty) {
  char s[] = "";

  ck_assert(!IsAlphaNumeric(s, 2));
}
END_TEST

START_TEST(IsAlphaNumericGreaterSize) {
  char s[] = "asdf";

  ck_assert(!IsAlphaNumeric(s, 2));
}
END_TEST

START_TEST(IsAlphaNumericInvalidContent) {
  char s[] = "asdf;123";

  ck_assert(!IsAlphaNumeric(s, 12));
}
END_TEST

START_TEST(IsAlphaNumericValidLessSize) {
  char s[] = "asd123";

  ck_assert(IsAlphaNumeric(s, 10));
}
END_TEST

START_TEST(IsAlphaNumericValidEqualSize) {
  char s[] = "asd123";

  ck_assert(IsAlphaNumeric(s, 6));
}
END_TEST

START_TEST(IsSignedNumericEmpty) {
  char s[] = "";

  ck_assert(!IsSignedNumeric(s, 2));
}

START_TEST(IsSignedNumericGreaterSize) {
  char s[] = "C0123";

  ck_assert(!IsSignedNumeric(s, 2));
}
END_TEST

START_TEST(IsSignedNumericInvalidContentSign) {
  char s[] = "R001234";

  ck_assert(!IsSignedNumeric(s, 10));
}
END_TEST

START_TEST(IsSignedNumericInvalidContentNumeric) {
  char s[] = "D;01234";

  ck_assert(!IsSignedNumeric(s, 10));
}
END_TEST

START_TEST(IsSignedNumericValidLessSize) {
  char s[] = "C1234";

  ck_assert(IsSignedNumeric(s, 10));
}
END_TEST

START_TEST(IsSignedNumericValidEqualSize) {
  char s[] = "D1234";

  ck_assert(IsSignedNumeric(s, 5));
}
END_TEST

START_TEST(IsDateTimeEmpty) {
  char s[] = "";

  ck_assert(!IsDateTime(s, 19));
}

START_TEST(IsDateTimeNotDate) {
  char s[] = "asdfasdf";

  ck_assert(!IsDateTime(s, 19));
}

START_TEST(IsDateTimeNoTime) {
  char s[] = "2024-01-27         ";

  ck_assert(!IsDateTime(s, 19));
}

START_TEST(IsDateTimeInvalidFormat) {
  char s[] = "2024-01-27 12:00:23;";

  ck_assert(!IsDateTime(s, 19));
}

START_TEST(IsDateTimeNotNormalized) {
  char s[] = "2024-13-32 12:00:23";

  ck_assert(!IsDateTime(s, 19));
}

START_TEST(IsDateTimeValid) {
  char s[] = "2003-01-27 06:45:00";

  ck_assert(IsDateTime(s, 19));
}

Suite* ValidationSuite(void) {
  Suite* suite;
  TCase* tc_core;

  suite = suite_create("ValidationTests");
  tc_core = tcase_create("ValidationTestsCore");

  tcase_add_test(tc_core, IsNumericEmpty);
  tcase_add_test(tc_core, IsNumericGreaterSize);
  tcase_add_test(tc_core, IsNumericInvalidContent);
  tcase_add_test(tc_core, IsNumericValidLessSize);
  tcase_add_test(tc_core, IsNumericValidEqualSize);
  tcase_add_test(tc_core, IsAlphaNumericEmpty);
  tcase_add_test(tc_core, IsAlphaNumericGreaterSize);
  tcase_add_test(tc_core, IsAlphaNumericInvalidContent);
  tcase_add_test(tc_core, IsAlphaNumericValidLessSize);
  tcase_add_test(tc_core, IsAlphaNumericValidEqualSize);
  tcase_add_test(tc_core, IsSignedNumericEmpty);
  tcase_add_test(tc_core, IsSignedNumericGreaterSize);
  tcase_add_test(tc_core, IsSignedNumericInvalidContentSign);
  tcase_add_test(tc_core, IsSignedNumericInvalidContentNumeric);
  tcase_add_test(tc_core, IsSignedNumericValidLessSize);
  tcase_add_test(tc_core, IsSignedNumericValidEqualSize);
  tcase_add_test(tc_core, IsDateTimeEmpty);
  tcase_add_test(tc_core, IsDateTimeNotDate);
  tcase_add_test(tc_core, IsDateTimeNoTime);
  tcase_add_test(tc_core, IsDateTimeInvalidFormat);
  tcase_add_test(tc_core, IsDateTimeNotNormalized);
  tcase_add_test(tc_core, IsDateTimeValid);

  suite_add_tcase(suite, tc_core);

  return suite;
}

#include "test.h"

#include <stdlib.h>

int main(void) {
  SRunner* suite_runner;

  suite_runner = srunner_create(AccountsSuite());
  srunner_add_suite(suite_runner, ValidationSuite());
  // srunner_add_suite(suite_runner, s21_sub_suite());
  // srunner_add_suite(suite_runner, s21_mult_number_suite());
  // srunner_add_suite(suite_runner, s21_mult_matrix_suite());
  // srunner_add_suite(suite_runner, s21_transpose_suite());
  // srunner_add_suite(suite_runner, s21_determinant_suite());
  // srunner_add_suite(suite_runner, s21_calc_components_suite());
  // srunner_add_suite(suite_runner, s21_inverse_suite());
  // srunner_add_suite(suite_runner, s21_create_suite());

  srunner_run_all(suite_runner, CK_NORMAL);

  int number_failed = srunner_ntests_failed(suite_runner);

  srunner_free(suite_runner);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

#include "test.h"

#include <stdlib.h>

int main(void) {
  SRunner* suite_runner;

  suite_runner = srunner_create(AccountsSuite());
  srunner_add_suite(suite_runner, ValidationSuite());
  srunner_add_suite(suite_runner, MessageSuite());
  srunner_add_suite(suite_runner, DeserializationSuite());
  srunner_add_suite(suite_runner, AccountDeserializationSuite());
  srunner_add_suite(suite_runner, SqlSuite());

  srunner_run_all(suite_runner, CK_NORMAL);

  int number_failed = srunner_ntests_failed(suite_runner);

  srunner_free(suite_runner);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

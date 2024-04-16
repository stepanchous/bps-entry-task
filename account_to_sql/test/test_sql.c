#include "test.h"

#include <check.h>
#include <stdlib.h>

#include "account_to_sql.h"

START_TEST(InsertNoLedger) {
  char* buff;
  size_t size;
  FILE* output = open_memstream(&buff, &size);

  struct Account account = {
      .number = "123",
      .balance = -32,
      .update_date = 100,
      .update_time = 78,
  };

  SqlInsertAccount(&account, output);

  char expected[] =
      "INSERT INTO T_ACCOUNT (ACCOUNT_NO, AVAIL_BAL, LEDGER_BAL, UPD_DATE, "
      "UPD_TIME) VALUES ('123', -32, NULL, 100, 78);\n";

  fflush(output);

  ck_assert_str_eq(buff, expected);

  fclose(output);
  free(buff);
}
END_TEST

START_TEST(InsertLedger) {
  char* buff;
  size_t size;
  FILE* output = open_memstream(&buff, &size);

  struct Account account = {
      .number = "123",
      .balance = -32,
      .optional_ledger_balance = {.has_value = true, .ledger_balance = 50},
      .update_date = 100,
      .update_time = 78,
  };

  SqlInsertAccount(&account, output);

  char expected[] =
      "INSERT INTO T_ACCOUNT (ACCOUNT_NO, AVAIL_BAL, LEDGER_BAL, UPD_DATE, "
      "UPD_TIME) VALUES ('123', -32, 50, 100, 78);\n";

  fflush(output);

  ck_assert_str_eq(buff, expected);

  fclose(output);
  free(buff);
}
END_TEST

START_TEST(TestCommit) {
  char* buff;
  size_t size;
  FILE* output = open_memstream(&buff, &size);

  SqlCommit(output);

  char expected[] = "COMMIT;\n";

  fflush(output);

  ck_assert_str_eq(buff, expected);

  fclose(output);
  free(buff);
}
END_TEST

Suite* SqlSuite(void) {
  Suite* suite;
  TCase* tc_core;

  suite = suite_create("AccountsTests");
  tc_core = tcase_create("AccountsTestsCore");

  tcase_add_test(tc_core, InsertNoLedger);
  tcase_add_test(tc_core, InsertLedger);
  tcase_add_test(tc_core, TestCommit);

  suite_add_tcase(suite, tc_core);

  return suite;
}

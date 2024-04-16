#include "test.h"

#include <stdlib.h>

#include "account.h"

START_TEST(NewAccountsEmpty) {
  struct Accounts accounts = NewAccounts();

  ck_assert_ptr_null(accounts.data);
  ck_assert_uint_eq(accounts.size, 0);
  ck_assert_uint_eq(accounts.capacity_, 0);

  DeleteAccounts(&accounts);
}
END_TEST

START_TEST(AccountsAppendOne) {
  struct Accounts accounts = NewAccounts();

  struct Account account = (struct Account){
      .number = "",
      .balance = 0,
      .optional_ledger_balance =
          {
              .has_value = false,
              .ledger_balance = 0,
          },
      .update_date = 0,
      .update_time = 0,

  };

  AppendAccount(&accounts, &account);

  struct Account* expected = malloc(sizeof(struct Account));
  expected[0] = account;

  ck_assert(IsEqualAccount(&accounts.data[0], &expected[0]));
  ck_assert_uint_eq(accounts.size, 1);
  ck_assert_uint_eq(accounts.capacity_, 1);

  free(expected);
  DeleteAccounts(&accounts);
}
END_TEST

START_TEST(AccountsAppendMultiple) {
  struct Accounts accounts = NewAccounts();

  struct Account account = (struct Account){
      .number = "",
      .balance = 0,
      .optional_ledger_balance =
          {
              .has_value = false,
              .ledger_balance = 0,
          },
      .update_date = 0,
      .update_time = 0,

  };

  AppendAccount(&accounts, &account);
  AppendAccount(&accounts, &account);
  AppendAccount(&accounts, &account);

  struct Account* expected = malloc(3 * sizeof(struct Account));
  expected[0] = account;
  expected[1] = account;
  expected[2] = account;

  ck_assert(IsEqualAccount(&accounts.data[0], &expected[0]));
  ck_assert(IsEqualAccount(&accounts.data[1], &expected[1]));
  ck_assert(IsEqualAccount(&accounts.data[2], &expected[2]));
  ck_assert_uint_eq(accounts.size, 3);
  ck_assert_uint_eq(accounts.capacity_, 4);

  free(expected);
  DeleteAccounts(&accounts);
}
END_TEST

Suite* AccountsSuite(void) {
  Suite* suite;
  TCase* tc_core;

  suite = suite_create("AccountsTests");
  tc_core = tcase_create("AccountsTestsCore");

  tcase_add_test(tc_core, NewAccountsEmpty);
  tcase_add_test(tc_core, AccountsAppendOne);
  tcase_add_test(tc_core, AccountsAppendMultiple);

  suite_add_tcase(suite, tc_core);

  return suite;
}

#include "test.h"

#include <check.h>

#include "account_deserialization.h"
#include "message.h"

START_TEST(AccountDeserializationInvalidTag) {
  struct DataMessage data_message =
      DataMessageBuilder(4, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 10:00:00"),
                         FieldMessageBuilder("ST", 2, "sc"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) != 0);

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationNotEnoughFields) {
  struct DataMessage data_message =
      DataMessageBuilder(2, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 10:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) != 0);

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationDuplicateNumber) {
  struct DataMessage data_message =
      DataMessageBuilder(4, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 10:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) != 0);

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationDuplicateBalance) {
  struct DataMessage data_message =
      DataMessageBuilder(4, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 10:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) != 0);

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationDuplicateUpdateTime) {
  struct DataMessage data_message =
      DataMessageBuilder(4, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 10:00:00"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 10:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) != 0);

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationDuplicateLedgerBalance) {
  struct DataMessage data_message =
      DataMessageBuilder(5, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("LB", 13, "D000012312312"),
                         FieldMessageBuilder("LB", 13, "D000012312312"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 10:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) != 0);

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationInvalidNumber) {
  struct DataMessage data_message =
      DataMessageBuilder(4, FieldMessageBuilder("NA", 4, ";101"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("LB", 13, "D000012312312"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 10:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) != 0);

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationInvalidBalance) {
  struct DataMessage data_message =
      DataMessageBuilder(4, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("AB", 13, ";000000000001"),
                         FieldMessageBuilder("LB", 13, "D000012312312"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 10:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) != 0);

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationInvalidLedgerBalance) {
  struct DataMessage data_message =
      DataMessageBuilder(4, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("LB", 13, "Dk00012312312"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 10:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) != 0);

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationInvalidUpdateTime) {
  struct DataMessage data_message =
      DataMessageBuilder(4, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("LB", 13, "D000012312312"),
                         FieldMessageBuilder("UT", 19, "2022-05-01 -1:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) != 0);

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationValidNoLedger) {
  struct DataMessage data_message =
      DataMessageBuilder(3, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("UT", 19, "2000-01-01 00:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) == 0);

  struct Account expected = {
      .number = "0101",
      .balance = 1,
      .update_date = 20000101,
      .update_time = 0,
  };

  ck_assert(IsEqualAccount(&account, &expected));

  DeleteDataMessage(&data_message);
}
END_TEST

START_TEST(AccountDeserializationValidWithLedger) {
  struct DataMessage data_message =
      DataMessageBuilder(4, FieldMessageBuilder("NA", 4, "0101"),
                         FieldMessageBuilder("AB", 13, "C000000000001"),
                         FieldMessageBuilder("LB", 13, "D000012312312"),
                         FieldMessageBuilder("UT", 19, "2000-01-01 00:00:00"));

  struct Account account;

  ck_assert(DeserializeAccount(&data_message, &account) == 0);

  struct Account expected = {
      .number = "0101",
      .balance = 1,
      .optional_ledger_balance =
          {
              .has_value = true,
              .ledger_balance = -12312312,
          },
      .update_date = 20000101,
      .update_time = 0,
  };

  ck_assert(IsEqualAccount(&account, &expected));

  DeleteDataMessage(&data_message);
}
END_TEST

Suite* AccountDeserializationSuite(void) {
  Suite* suite;
  TCase* tc_core;

  suite = suite_create("AccountsTests");
  tc_core = tcase_create("AccountsTestsCore");

  tcase_add_test(tc_core, AccountDeserializationInvalidTag);
  tcase_add_test(tc_core, AccountDeserializationNotEnoughFields);
  tcase_add_test(tc_core, AccountDeserializationDuplicateNumber);
  tcase_add_test(tc_core, AccountDeserializationDuplicateBalance);
  tcase_add_test(tc_core, AccountDeserializationDuplicateUpdateTime);
  tcase_add_test(tc_core, AccountDeserializationDuplicateLedgerBalance);
  tcase_add_test(tc_core, AccountDeserializationInvalidNumber);
  tcase_add_test(tc_core, AccountDeserializationInvalidBalance);
  tcase_add_test(tc_core, AccountDeserializationInvalidLedgerBalance);
  tcase_add_test(tc_core, AccountDeserializationInvalidUpdateTime);
  tcase_add_test(tc_core, AccountDeserializationValidNoLedger);
  tcase_add_test(tc_core, AccountDeserializationValidWithLedger);

  suite_add_tcase(suite, tc_core);

  return suite;
}

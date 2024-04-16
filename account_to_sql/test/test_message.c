#include "test.h"

#include <check.h>

#include "message.h"

START_TEST(EmptyInput) {
  char message[] = "";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  ck_assert_ptr_null(data_messages.data);
  ck_assert_uint_eq(data_messages.size, 0);

  fclose(input);
}

START_TEST(SingleMessageInvalidTag) {
  char message[] = ";A201";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  ck_assert_ptr_null(data_messages.data);
  ck_assert_uint_eq(data_messages.size, 0);

  fclose(input);
}

START_TEST(SingleMessageNoTag) {
  char message[] = "201";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  ck_assert_ptr_null(data_messages.data);
  ck_assert_uint_eq(data_messages.size, 0);

  fclose(input);
}

START_TEST(SingleMessageLongerTag) {
  char message[] = "ASD201";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  ck_assert_ptr_null(data_messages.data);
  ck_assert_uint_eq(data_messages.size, 0);

  fclose(input);
}

START_TEST(SingleMessageInvalidLength) {
  char message[] = "AS-12";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  ck_assert_ptr_null(data_messages.data);
  ck_assert_uint_eq(data_messages.size, 0);

  fclose(input);
}

START_TEST(SingleMessageGreaterLength) {
  char message[] = "AS1210101";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  ck_assert_ptr_null(data_messages.data);
  ck_assert_uint_eq(data_messages.size, 0);

  fclose(input);
}

START_TEST(SingleMessageLessLenth) {
  char message[] = "AS01123";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  ck_assert_ptr_null(data_messages.data);
  ck_assert_uint_eq(data_messages.size, 0);

  fclose(input);
}

START_TEST(SingleMessageSingleFieldValid) {
  char message[] = "AS0201";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  struct DataMessages expected = NewDataMessages();

  struct DataMessage expected_message =
      DataMessageBuilder(1, FieldMessageBuilder("AS", 2, "01"));
  MoveDataMessage(&expected, &expected_message);

  ck_assert(IsEqualDataMessages(&data_messages, &expected));

  DeleteDataMessages(&data_messages);
  DeleteDataMessages(&expected);

  fclose(input);
}

START_TEST(SingleMessageSingleFieldValidStartsWithWS) {
  char message[] = "  \nAS0201";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  struct DataMessages expected = NewDataMessages();

  struct DataMessage expected_message =
      DataMessageBuilder(1, FieldMessageBuilder("AS", 2, "01"));
  MoveDataMessage(&expected, &expected_message);

  ck_assert(IsEqualDataMessages(&data_messages, &expected));

  DeleteDataMessages(&data_messages);
  DeleteDataMessages(&expected);

  fclose(input);
}

START_TEST(SingleMessageMixedFieldsByValidity) {
  char message[] = "AS0201DS041";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  ck_assert_ptr_null(data_messages.data);
  ck_assert_uint_eq(data_messages.size, 0);

  DeleteDataMessages(&data_messages);

  fclose(input);
}

START_TEST(SingleMessageMultipleValid) {
  char message[] = "AS0201DS04asdf";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  struct DataMessages expected = NewDataMessages();

  struct DataMessage expected_message =
      DataMessageBuilder(2, FieldMessageBuilder("AS", 2, "01"),
                         FieldMessageBuilder("DS", 4, "asdf"));

  MoveDataMessage(&expected, &expected_message);

  ck_assert(IsEqualDataMessages(&data_messages, &expected));

  DeleteDataMessages(&data_messages);
  DeleteDataMessages(&expected);

  fclose(input);
}

START_TEST(MultipleMessageFirstValidNextInvalid) {
  char message[] = "AS0201DS041\n;a-1";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  ck_assert_ptr_null(data_messages.data);
  ck_assert_uint_eq(data_messages.size, 0);

  DeleteDataMessages(&data_messages);

  fclose(input);
}

START_TEST(MultipleMessageValid) {
  char message[] = "AS0201DS041000\nBA100000011111";
  FILE* input = fmemopen(message, strlen(message), "r");

  struct DataMessages data_messages = ReadDataMessages(input);

  struct DataMessages expected = NewDataMessages();

  struct DataMessage expected_message =
      DataMessageBuilder(2, FieldMessageBuilder("AS", 2, "01"),
                         FieldMessageBuilder("DS", 4, "1000"));

  MoveDataMessage(&expected, &expected_message);

  expected_message =
      DataMessageBuilder(1, FieldMessageBuilder("BA", 10, "0000011111"));

  MoveDataMessage(&expected, &expected_message);

  ck_assert(IsEqualDataMessages(&data_messages, &expected));

  DeleteDataMessages(&data_messages);
  DeleteDataMessages(&expected);

  fclose(input);
}

Suite* MessageSuite(void) {
  Suite* suite;
  TCase* tc_core;

  suite = suite_create("MessageTests");
  tc_core = tcase_create("MessageTestsCore");

  tcase_add_test(tc_core, SingleMessageInvalidTag);
  tcase_add_test(tc_core, SingleMessageNoTag);
  tcase_add_test(tc_core, SingleMessageLongerTag);
  tcase_add_test(tc_core, SingleMessageInvalidLength);
  tcase_add_test(tc_core, SingleMessageGreaterLength);
  tcase_add_test(tc_core, SingleMessageLessLenth);
  tcase_add_test(tc_core, EmptyInput);
  tcase_add_test(tc_core, SingleMessageSingleFieldValid);
  tcase_add_test(tc_core, SingleMessageMixedFieldsByValidity);
  tcase_add_test(tc_core, SingleMessageSingleFieldValidStartsWithWS);
  tcase_add_test(tc_core, SingleMessageMultipleValid);
  tcase_add_test(tc_core, MultipleMessageFirstValidNextInvalid);
  tcase_add_test(tc_core, MultipleMessageValid);

  suite_add_tcase(suite, tc_core);

  return suite;
}

#include "account.h"
#include "account_deserialization.h"
#include "flags.h"
#include "message.h"

int main(int argc, char** argv) {
  struct ProgramParameters params;

  if (ParseArgs(argc, argv, &params) != 0) {
    PrintUsage();
    return -1;
  }

  struct DataMessages data_messages = ReadDataMessages(stdin);

  if (data_messages.size == 0) {
    printf("Error reading input\n");
    return -1;
  }

  for (uint32_t i = 0; i < data_messages.size; ++i) {
    struct Account account;

    int err = DeserializeAccount(&data_messages.data[i], &account);

    if (err) {
      printf("Deserialization Error\n");
      return -1;
    }
  }

  DeleteDataMessages(&data_messages);
}

#include <stdio.h>

#include "account.h"
#include "account_deserialization.h"
#include "account_to_sql.h"
#include "flags.h"
#include "message.h"

int main(int argc, char** argv) {
  struct ProgramParameters params;

  if (ParseArgs(argc, argv, &params) != 0) {
    PrintUsage();
    return -1;
  }

  struct DataMessages data_messages = ReadDataMessages(stdin);
  int err = data_messages.size == 0;

  struct Accounts accounts = NewAccounts();

  if (!err) {
    for (uint32_t i = 0; i < data_messages.size && !err; ++i) {
      struct Account account;

      err = DeserializeAccount(&data_messages.data[i], &account);

      if (!err) {
        AppendAccount(&accounts, &account);
      } else {
        err = 1;
        printf("Deserialization Error\n");
      }
    }
  } else {
    printf("Error reading input\n");
  }

  for (uint32_t i = 0; i < accounts.size; ++i) {
    SqlInsertAccount(&accounts.data[i], stdout);

    if (CheckFlag(params.flags, COMMIT) &&
        (i + 1) % params.args.commit_limit == 0) {
      SqlCommit(stdout);
    }
  }

  DeleteDataMessages(&data_messages);
  DeleteAccounts(&accounts);
}

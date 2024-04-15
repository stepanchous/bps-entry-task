#include "account_message.h"
#include "flags.h"
#include "read_message.h"

int main(int argc, char** argv) {
  struct Config args = ParseArgs(argc, argv);

  if (args.err) {
    PrintUsage();
    return -1;
  }

  struct AccountMessages records = NewAccountMessages();

  if (ReadAccountRecords(stdin, &records) != 0) {
    printf("Error reading input\n");
  }

  DeleteAccountMessages(&records);
}

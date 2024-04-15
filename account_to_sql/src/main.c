#include "account.h"
#include "flags.h"
#include "read_message.h"

int main(int argc, char** argv) {
  struct Config args = ParseArgs(argc, argv);

  if (args.err) {
    PrintUsage();
    return -1;
  }

  struct AccountRecords records = NewAccountRecords();

  if (ReadAccountRecords(stdin, &records) != 0) {
    printf("Error reading input\n");
  }

  DeleteAccountRecords(&records);
}

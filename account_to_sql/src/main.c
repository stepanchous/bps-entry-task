#include "flags.h"

int main(int argc, char** argv) {
  struct Config args = ParseArgs(argc, argv);

  if (args.err) {
    PrintUsage();
    return -1;
  }
}

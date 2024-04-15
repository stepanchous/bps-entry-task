#ifndef BPS_FLAGS_H
#define BPS_FLAGS_H

#include <stdbool.h>
#include <stdint.h>

enum Flag {
  COMMIT = 1 << 0,
};

struct FlagArgs {
  uint32_t commit_limit;
};

struct ProgramParameters {
  uint32_t flags;
  struct FlagArgs args;
};

int ParseArgs(int argc, char** argv,
              struct ProgramParameters* program_parameters);

bool CheckFlag(uint32_t flags, enum Flag flag);

void PrintUsage(void);

#endif  // !BPS_FLAGS_H

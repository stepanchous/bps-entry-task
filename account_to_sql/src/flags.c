#include "flags.h"

#include <getopt.h>
#include <stdio.h>

struct Config ParseArgs(int argc, char** argv) {
  struct Config config = {
      .err = 0,
      .program_parameters = {.flags = 0, .args = {.commit_limit = 0}}};

  int option;

  while (!config.err && (option = getopt(argc, argv, "c:")) != -1) {
    switch (option) {
      case 'c': {
        config.program_parameters.flags |= COMMIT;

        if (sscanf(optarg, "%u",
                   &config.program_parameters.args.commit_limit) != 1) {
          config.err = 1u;

          fprintf(stderr, "%s: argument error: '%s'\n", argv[0], optarg);
        }

        break;
      }
      case '?': {
        config.err = 1u;
        break;
      }
    }
  }

  return config;
}

bool CheckFlag(uint32_t flags, enum Flag flag) { return flags & flag; }

void PrintUsage(void) { printf("usage: acct2sql [-c <commit limit>]\n"); }

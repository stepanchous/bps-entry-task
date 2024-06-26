#include "flags.h"

#include <getopt.h>
#include <stdio.h>

#include "value_validation.h"

int ParseArgs(int argc, char** argv,
              struct ProgramParameters* program_parameters) {
  int err = 0;

  *program_parameters = (struct ProgramParameters){.flags = 0,
                                                   .args = {
                                                       .commit_limit = 0,
                                                   }};

  int option;

  while (!err && (option = getopt(argc, argv, "c:")) != -1) {
    switch (option) {
      case 'c': {
        if (!IsNumeric(optarg, 11) ||
            sscanf(optarg, "%u", &program_parameters->args.commit_limit) != 1 ||
            program_parameters->args.commit_limit == 0) {
          err = 1;

          fprintf(stderr, "%s: argument error: '%s'\n", argv[0], optarg);
        } else {
          program_parameters->flags |= COMMIT;
        }

        break;
      }
      case '?': {
        err = 1;
        break;
      }
    }
  }

  return err;
}

bool CheckFlag(uint32_t flags, enum Flag flag) { return flags & flag; }

void PrintUsage(void) { printf("usage: acct2sql [-c <commit limit>]\n"); }

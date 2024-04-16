#ifndef BPS_ACCOUNT_TO_SQL
#define BPS_ACCOUNT_TO_SQL

#include <stdio.h>

#include "account.h"

void SqlInsertAccount(const struct Account* account, FILE* output);
void SqlCommit(FILE* output);

#endif  // !BPS_ACCOUNT_TO_SQL

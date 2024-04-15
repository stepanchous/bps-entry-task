#ifndef BPS_READ_MESSAGE_H
#define BPS_READ_MESSAGE_H

#include <stdio.h>

#include "account.h"

int ReadAccountRecords(FILE* input, struct AccountRecords* account_records);

#endif  // !BPS_READ_MESSAGE_H

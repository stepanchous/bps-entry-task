#ifndef BPS_READ_MESSAGE_H
#define BPS_READ_MESSAGE_H

#include <stdio.h>

#include "account_message.h"

int ReadAccountRecords(FILE* input, struct AccountMessages* account_records);

#endif  // !BPS_READ_MESSAGE_H

#ifndef BPS_ACCOUNT_DESERIALIZATION_H
#define BPS_ACCOUNT_DESERIALIZATION_H

#include "account.h"
#include "message.h"

int DeserializeAccount(const struct DataMessage* message,
                       struct Account* account);

#endif  // !BPS_ACCOUNT_DESERIALIZATION_H

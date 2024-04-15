#ifndef BPS_ACCOUNT_DESERIALIZATION_H
#define BPS_ACCOUNT_DESERIALIZATION_H

#include "account.h"
#include "account_message.h"

struct Account DeserializeAccount(const struct AccountMessage* message);

#endif  // !BPS_ACCOUNT_DESERIALIZATION_H

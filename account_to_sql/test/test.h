#ifndef BPS_TEST_H
#define BPS_TEST_H

#include <check.h>

Suite* AccountsSuite(void);
Suite* ValidationSuite(void);
Suite* MessageSuite(void);
Suite* DeserializationSuite(void);
Suite* AccountDeserializationSuite(void);
Suite* SqlSuite(void);

#endif  // !BPS_TEST_H

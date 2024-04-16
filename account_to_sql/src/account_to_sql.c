#include "account_to_sql.h"

#define TABLE_NAME "T_ACCOUNT"
#define ACCOUNT_NUMBER_COL "ACCOUNT_NO"
#define ACCOUNT_BALANCE_COL "AVAIL_BAL"
#define ACCOUNT_LEDGER_BALANCE_COL "LEDGER_BAL"
#define ACCOUNT_UPDATE_DATE_COL "UPD_DATE"
#define ACCOUNT_UPDATE_TIME_COL "UPD_TIME"

void SqlInsertAccount(const struct Account* account, FILE* output) {
  fprintf(output, "INSERT INTO %s ", TABLE_NAME);
  fprintf(output, "(%s, %s, %s, %s, %s) ", ACCOUNT_NUMBER_COL,
          ACCOUNT_BALANCE_COL, ACCOUNT_LEDGER_BALANCE_COL,
          ACCOUNT_UPDATE_DATE_COL, ACCOUNT_UPDATE_TIME_COL);

  fprintf(output, "VALUES ('%s', %ld, ", account->number, account->balance);

  if (account->optional_ledger_balance.has_value) {
    fprintf(output, "%ld, ", account->optional_ledger_balance.ledger_balance);
  } else {
    fprintf(output, "NULL, ");
  }

  fprintf(output, "%lu, %u);\n", account->update_date, account->update_time);
}

void SqlCommit(FILE* output) { fprintf(output, "COMMIT;\n"); }

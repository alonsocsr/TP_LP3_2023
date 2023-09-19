#include <pthread.h>
#include <stdio.h>
#include <string.h>

/* An array of balances in accounts, indexed by account number.*/

float account_balances[2];

/* Transfer DOLLARS from account FROM_ACCT to account TO_ACCT. Return
0 if the transaction succeeded, or 1 if the balance FROM_ACCT is
too small. */

typedef struct {
  int dollars;
  int from_acct;
  int to_acct;
} BankTransaction;

void* process_transaction(void* arg)
{
  BankTransaction t = *(BankTransaction*)arg;

  int old_cancel_state;

  /* Check the balance in FROM_ACCT. */
  if (account_balances[t.from_acct] < t.dollars){
    printf("Insufficient balance in Account %d\n", account_balances[t.from_acct]);
    return NULL;
  }

  /* Begin critical section. */
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
  
  /* Move the money. */
  account_balances[t.to_acct] += t.dollars;
  account_balances[t.from_acct] -= t.dollars;
  printf("Transfer %d$ from Account %d to Account %d \n" , t.dollars, t.from_acct, t.to_acct);
  
  /* End critical section. */
  pthread_setcancelstate(old_cancel_state, NULL);

  return NULL;
}

int main (){

  pthread_t thread;

  account_balances[0] = 10000;
  account_balances[1] = 10000;

  BankTransaction transfer;
  transfer.dollars = 600;
  transfer.from_acct = 0;
  transfer.to_acct = 1;

  pthread_create(&thread, NULL, process_transaction, &transfer);

  pthread_join(thread, NULL);

  return 0;
}
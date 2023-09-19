#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* Compute successive prime numbers (very inefficiently). Return the
Nth prime number, where N is the value pointed to by *ARG. */

void* compute_prime(void *arg)
{
  // an integer is reserved dynamically to return his pointer as a pointer to void
  int *value = (int*)malloc(sizeof(int)); 
  int candidate = 2;
  int n = *((int *)arg);

  while (1){
    int factor;
    int is_prime = 1;

    /* Test primality by successive division. */
    for (factor = 2; factor < candidate; ++factor)
      if (candidate % factor == 0){
        is_prime = 0;
        break;
      }
    /* Is this the prime number we’re looking for? */
    if (is_prime) {
      if (--n == 0){
        /* Return the desired prime number as the thread return value.*/
        *value = candidate;
        return (void*)value;
      }
    }
    ++candidate;
  }
  return NULL;
}

  int main()
  {
    pthread_t thread;
    int which_prime = 5000;

    // a pointer to void that we gonna use to capture the thread return value
    void *ptr_void;

    /* Start the computing thread, up to the 5,000th prime number. */
    pthread_create(&thread, NULL, &compute_prime, &which_prime);
    /* Do some other work here... */
    /* Wait for the prime number thread to complete, and get the result.*/
    pthread_join (thread, &ptr_void);
    
    /*cast the return value to a pointer, there's not gonna be an error because we have reserved the space for an integer*/
    int prime = *((int *)ptr_void);
    /* Print the largest prime it computed. */
    printf("The %dth prime number is % d.\n", which_prime, prime);

    /*free the memory that we have reserved before*/
    free(ptr_void);
    return 0;
  }
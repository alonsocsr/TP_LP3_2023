#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*Detached threads are often used for tasks that need to run in the background or for lightweight threads where the program doesn't need to wait for their completion. Examples include background data processing, logging, or daemon-like tasks.*/

void *thread_function(void *thread_arg)
{
  printf("Detached thread started.\n");
  sleep(3); // Simulate some work
  printf("Detached thread finished.\n");
  return NULL;
}
int main()
{
  pthread_attr_t attr;
  pthread_t thread;

  // Initialize thread attributes with the default values
  pthread_attr_init(&attr);

  // Set the thread as detached
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  
  // Create the detached thread
  pthread_create(&thread, &attr, &thread_function, NULL);
  
  // Main thread continues its work
  printf("Main thread continues.\n");

  // Clean up the thread attribute
  pthread_attr_destroy(&attr);

  // Sleep to allow the detached thread to finish (optional)
  sleep(4);

  /* No need to join the second thread.*/
  return 0;
}
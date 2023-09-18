#include <malloc.h>
#include <pthread.h>
#include <unistd.h>

/* Allocate a temporary buffer.*/
void *allocate_buffer(size_t size)
{
  return malloc(size);
}

/* Deallocate a temporary buffer.*/
void deallocate_buffer(void *buffer)
{
  free(buffer);
}

void* do_some_work()
{
  /* Allocate a temporary buffer. */
  void *temp_buffer = allocate_buffer(1024);
  
  /* Register a cleanup handler for this buffer, to deallocate it in
  case the thread exits or is cancelled. */
  pthread_cleanup_push(deallocate_buffer, temp_buffer);
  
  /* Do some work here that might call pthread_exit or might be
  cancelled... */
  for (int i = 1; i <= 5; i++) {
    printf("Working... %d seconds\n", i);
    sleep(1);
    if (i == 3) {
      printf("Cancellation requested...\n");
      pthread_cancel(pthread_self());
    }
  }

  printf("Work completed.\n");
  /* Unregister the cleanup handler. Because we pass a nonzero value,
  this actually performs the cleanup by calling
  deallocate_buffer. */
  pthread_cleanup_pop(1);
}

int main(){

  pthread_t thread;

  // Create a thread
  if (pthread_create(&thread, NULL, do_some_work, NULL) != 0) {
    perror("pthread_create fail");
    return 1;
  }

  // Wait for the thread to finish
  if (pthread_join(thread, NULL) != 0) {
    perror("pthread_join fail");
    return 1;
  }

  printf("Thread has exited.\n");

  return 0;
}
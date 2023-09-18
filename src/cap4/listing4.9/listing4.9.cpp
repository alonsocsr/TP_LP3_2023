#include <pthread.h>
#include <malloc.h>
#include <unistd.h>

class ThreadExitException
{
public:
  /* Create an exception-signaling thread exit with RETURN_VALUE.*/
  ThreadExitException(void *return_value)
    : thread_return_value_(return_value)
  {
  }
  /* Actually exit the thread, using the return value provided in the
  constructor. */
  void *DoThreadExit()
  {
    pthread_exit(thread_return_value_);
  }

private:
  /* The return value that will be used when exiting the thread.*/
  void *thread_return_value_;
};

int should_exit_thread_immediately(){
  return 1;
}


void do_some_work()
{
  while (1)
  {
    /* Do some useful things here...*/
    for (int i = 1; i <= 2; i++) {
      printf("Working... %d seconds\n", i);
      sleep(1);
    }
    if (should_exit_thread_immediately())
      throw ThreadExitException(/* thread’s return value = */ NULL);
  }
}

void *thread_function(void *)
{
  try
  {
    do_some_work();
  }
  catch (ThreadExitException ex)
  {
    /* Some function indicated that we should exit the thread.*/
    ex.DoThreadExit();
  }
  return NULL;
}

int main(){

  pthread_t thread;

  // Create a thread
  if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
    perror("pthread create fail");
    return 1;
  }

  // Wait for the thread to finish
  if (pthread_join(thread, NULL) != 0) {
    perror("pthread join fail");
    return 1;
  }

  return 0;
}
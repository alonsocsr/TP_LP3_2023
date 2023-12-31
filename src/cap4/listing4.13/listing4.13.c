#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define MAX_THREADS 5

int thread_flag;
pthread_mutex_t thread_flag_mutex;

void initialize_flag()
{
  pthread_mutex_init(&thread_flag_mutex, NULL);
  thread_flag = 0;
}

void do_work(){
  for (int i = 1; i <= 2; i++) {
    printf("Working... %d seconds\n", i);
    sleep(1);
  }
}

/* Calls do_work repeatedly while the thread flag is set; otherwise spins. */
void *thread_function(void *thread_arg)
{
  while (1)
  {
    int flag_is_set;

    /* Protect the flag with a mutex lock. */
    pthread_mutex_lock(&thread_flag_mutex);
    flag_is_set = thread_flag;
    pthread_mutex_unlock(&thread_flag_mutex);

    if (flag_is_set)
      do_work();
    
    /* Else don’t do anything. Just loop again. */
  }
  return NULL;
}


/* Sets the value of the thread flag to FLAG_VALUE.*/
void set_thread_flag(int flag_value)
{
  /* Protect the flag with a mutex lock. */
  pthread_mutex_lock(&thread_flag_mutex);
  thread_flag = flag_value;
  pthread_mutex_unlock(&thread_flag_mutex);
}

int main()
{
  initialize_flag();

  pthread_t thread[MAX_THREADS];

  set_thread_flag(1);

  // Create a thread
  for (int i = 0; i < MAX_THREADS; i++)
  {
    if (pthread_create(&thread[i], NULL, thread_function, NULL) != 0)
    {
      perror("pthread_create fail");
      return 1;
    }
  }

  set_thread_flag(0);

  // Wait for the thread to finish
  for (int i = 0; i < MAX_THREADS; i++)
  {
    if (pthread_join(thread[i], NULL) != 0)
    {
      perror("pthread_join fail");
      return 1;
    }
  }
}

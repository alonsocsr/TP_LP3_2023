#include <malloc.h>
#include <pthread.h>

#define MAX_THREADS 5

struct job
{
  /* Link field for linked list.*/
  struct job *next;
  int limit; /*upper limit to calculate the prime number*/
};

/* A linked list of pending jobs.*/
struct job *job_queue;

/*function that calcule the thprime number*/
void process_job(struct job *current_job)
{

  int candidate = 2;
  int n = current_job->limit;

  while (1)
  {
    int factor;
    int is_prime = 1;

    /* Test primality by successive division. */
    for (factor = 2; factor < candidate; ++factor)
      if (candidate % factor == 0)
      {
        is_prime = 0;
        break;
      }
    /* Is this the prime number we’re looking for? */
    if (is_prime)
    {
      if (--n == 0)
      {
        printf("The %dth prime number is % d.\n", current_job->limit, candidate);
        return;
      }
    }
    ++candidate;
  }
}

/* Process queued jobs until the queue is empty.*/
void *thread_function(void *arg)
{
  while (job_queue != NULL)
  {
    /* Get the next available job. */
    struct job *next_job = job_queue;
    /* Remove this job from the list. */
    job_queue = job_queue->next;
    /* Carry out the work. */
    process_job(next_job);
    /* Clean up. */
    free(next_job);
  }
  return NULL;
}

// Function to add an element
void add(int data)
{
  struct job *newNode = (struct job *)malloc(sizeof(struct job));
  newNode->limit = data;
  newNode->next = NULL;

  if (job_queue == NULL)
  {
    job_queue = newNode;
    return;
  }

  newNode->next = job_queue;
  job_queue = newNode;
}

int main()
{

  job_queue = NULL; /*linked list empty*/
  pthread_t thread[MAX_THREADS];

  add(5);
  add(10);
  add(30);
  add(50);
  add(100);

  // Create a thread
  for (int i = 0; i < MAX_THREADS; i++)
  {
    if (pthread_create(&thread[i], NULL, thread_function, NULL) != 0)
    {
      perror("pthread_create fail");
      return 1;
    }
  }

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
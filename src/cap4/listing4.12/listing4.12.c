#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define MAX_THREADS 5

struct job
{
  struct job *next;   /* Link field for linked list.*/
  int limit;           /*upper limit to calculate the prime number*/
};

/* A linked list of pending jobs.*/
struct job *job_queue;

/* A mutex protecting job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/* A semaphore counting the number of jobs in the queue.*/
sem_t job_queue_count;

/* Perform one-time initialization of the job queue.*/
void initialize_job_queue()
{
  /* The queue is initially empty. */
  job_queue = NULL;
  /* Initialize the semaphore which counts jobs in the queue.
  initial value should be zero. */
  sem_init(&job_queue_count, 0, 0);
}

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
  while (1)
  {
    struct job *next_job;
    /* Wait on the job queue semaphore. If its value is positive,
    indicating that the queue is not empty, decrement the count by
    1. If the queue is empty, block until a new job is enqueued. */
    sem_wait(&job_queue_count);

    /* Lock the mutex on the job queue. */
    pthread_mutex_lock(&job_queue_mutex);
    /* Because of the semaphore, we know the queue is not empty. Get
    the next available job. */
    next_job = job_queue;
    /* Remove this job from the list. */
    job_queue = job_queue->next;
    /* Unlock the mutex on the job queue because we’re done with the
    queue for now. */
    pthread_mutex_unlock(&job_queue_mutex);

    /* Carry out the work. */
    process_job(next_job);
    /* Clean up. */
    free(next_job);
  }
  return NULL;
}

/* Add a new job to the front of the job queue.*/
void enqueue_job(int data)
{
  struct job *new_job;
  /* Allocate a new job object. */
  new_job = (struct job *)malloc(sizeof(struct job));
  /* Set the other fields of the job struct here... */
  new_job->limit = data;

  /* Lock the mutex on the job queue before accessing it.*/
  pthread_mutex_lock(&job_queue_mutex);
  /* Place the new job at the head of the queue. */
  new_job->next = job_queue;
  job_queue = new_job;

  /* Post to the semaphore to indicate that another job is available.
  threads are blocked, waiting on the semaphore, one will become
  unblocked so it can process the job. */
  sem_post(&job_queue_count);

  /* Unlock the job queue mutex. */
  pthread_mutex_unlock(&job_queue_mutex);
}


int main()
{

  initialize_job_queue();

  pthread_t thread[MAX_THREADS];

  enqueue_job(5);
  enqueue_job(10);
  enqueue_job(30);
  enqueue_job(50);
  enqueue_job(100);

  // Create a thread
  for (int i = 0; i < MAX_THREADS; i++)
  {
    if (pthread_create(&thread[i], NULL, thread_function, NULL) != 0)
    {
      perror("pthread_create fail");
      return 1;
    }
  }

  enqueue_job(20);
  enqueue_job(60);
  enqueue_job(15);

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
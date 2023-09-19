#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

sig_atomic_t sigusr1_count = 0;
int child_status;

void handler(int signal_number)
{
  ++sigusr1_count;
}

int main()
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = &handler;
  sigaction(SIGUSR1, &sa, NULL);

  // Create a child process
  pid_t child_pid = fork();

  if (child_pid != 0)
  {
    // This is the parent process
    printf("Parent process sending SIGUSR1 to the child (PID: %d)...\n", child_pid);

    // Send SIGUSR1 to the child process
    if (kill(child_pid, SIGUSR1) == 0)
      printf("Sent SIGUSR1 signal to child process (PID: %d)\n", child_pid);
    else
      perror("signal error");

    /* Wait for the child process to complete. */
    wait(&child_status);
    if (WIFEXITED(child_status))
      printf("The child process exited normally, with exit code %d\n", WEXITSTATUS(child_status));
    else
      printf("The child process exited abnormally\n");
  }
  else
  {
    // This is the child process
    printf("Child process waiting for SIGUSR1 signal...\n");
    
    printf("SIGUSR1 was raised % d times\n", sigusr1_count);
  }

  return 0;
}
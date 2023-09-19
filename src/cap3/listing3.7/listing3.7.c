#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

sig_atomic_t child_exit_status;

void clean_up_child_process(int signal_number)
{
  /* Clean up the child process. */
  int status;
  wait(&status);
  /* Store its exit status in a global variable.*/
  child_exit_status = status;
}

int main()
{
  /* Handle SIGCHLD by calling clean_up_child_process. */
  struct sigaction sigchld_action;
  memset(&sigchld_action, 0, sizeof(sigchld_action));
  sigchld_action.sa_handler = &clean_up_child_process;
  sigaction(SIGCHLD, &sigchld_action, NULL);
  
  // Create a child process
  pid_t child_pid = fork();

  if (child_pid != 0)
  {
    // This is the parent process
    printf ("This is the parent process, with id %d\n", (int) getpid ());
    sleep(2);
    printf("Child exit status %d\n", child_exit_status);
  }
  else
  {
    // This is the child process
    printf ("This is the child process, with id %d\n", (int) getpid ());
  }

  return 0;
}
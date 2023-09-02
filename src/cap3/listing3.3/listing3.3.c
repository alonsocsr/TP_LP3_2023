#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
    //pid_t --> tipo de dato para identificación de procesos.
    pid_t child_pid;
    //Este es el id de proceso del programa actual.	
    printf ("the main program process ID is %d\n", (int) getpid ());
    //Desde acá duplicamos el programa actual desde el punto
    child_pid = fork ();

    //Dentro del if se ejecutará sólamente el proceso padre.
    //Si el child_pid es distinto de cero, significa que estamos en el
    //proceso padre.
    if (child_pid != 0) {
        printf ("this is the parent process, with id %d\n", (int) getpid ());
        printf ("the child’s process ID is %d\n", (int) child_pid);
    }
    //El else sólamente se ejecutará en el proceso hijo
    else
        printf ("this is the child process, with id %d\n", (int) getpid ());
        //printf ("this is the child process, which returns  %d\n", (int) child_pid);
    return 0;
}

/*El valor de retorno del proceso padre es el ID de proceso.
  El valor de retorno del proceso hijo es 0.
*/
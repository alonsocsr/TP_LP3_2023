#include <stdio.h>
#include <unistd.h>

int main (){
    //Esta linea muestra el ID de este programa
    printf ("The process ID is %d\n", (int) getpid ());
    //Esta línea muestra el ID del proceso padre de este programa:
    //El shell que lo ejecuta en este caso.
    printf ("The parent process ID is %d\n", (int) getppid ());
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
int main (){
    //Se pone Const antes del char* para que no tire error de compilación
    const char* server_name = getenv ("SERVER_NAME");
    if (server_name == NULL)
        /* The SERVER_NAME environment variable was not set. Use the
        default. */
        server_name = "server.reaper-pc.com";
    printf ("accessing server %s\n", server_name);
    /* Access the server here... */
    return 0;
}
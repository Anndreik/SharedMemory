#include "shm_header.h"

static int received = 0;
void readerHandler(int sig)
{
    if (sig == SIGUSR1)
    {
        received = 1;
    }
}

int main(){
    signal(SIGUSR1,readerHandler);
    pid_t pid;
    pid = getpid();
    printf("Child %ld is starting...\n", (long)pid);
    while(1){
        while(!received);
        printf("Child %ld received SIGUSR1 signal.\n", (long)pid);
        received = 0;
        //exit(EXIT_SUCCESS);
    }
    return 0;
}
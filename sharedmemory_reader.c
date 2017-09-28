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
    while(true){
        while(!received);
        printf("SIGUSR1 received.\n");
        received = 0;
    }
    return 0;
}
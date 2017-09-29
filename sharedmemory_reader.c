#include "shm_header.h"

static volatile int received = 0;
void readerHandler(int sig)
{  
    if (sig == SIGUSR1)
    {
        received = 1;
        signal(SIGUSR1,readerHandler);
    }
    
}

int main(){
    if(signal(SIGUSR1,readerHandler) == SIG_ERR){
        printf("Binding Signal readerHandler error!\n");
        exit(EXIT_FAILURE);
    }
    int ShmID;
    int *ShmPTR;
    int number;
    ShmID = shmget(SHM_KEY, sizeof(int), 0666);
    pid_t pid;
    pid = getpid();
    printf("Child %ld is starting...\n", (long)pid);
    while(1){
        while(!received);
            //exit(EXIT_SUCCESS);
        //printf("Child %ld received SIGUSR1 signal.\n", (long)pid);
        //printf("Child %ld Reading from the shared memory...\n", (long)pid);
        ShmPTR = (int *) shmat(ShmID, NULL, 0);
        number = *ShmPTR;
        printf("Child reader process %ld - number in shared memory is : %d\n", (long)pid, number);
        received = 0;
        //exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}
#include "shm_header.h"

#define MAX_VALUE 1000
#define MIN_VALUE 2

static volatile int handle_var = 0;
static pid_t child_pid[3];

void writerHandler(int sig)
{
    int k;
    
    if (sig == SIGINT)
    {
        handle_var = 1;
        for( k = 0; k < 3; ++k){
            printf("Killing child %ld...\n", (long)child_pid[k]);
            kill(child_pid[k], SIGKILL);
        }
        signal(SIGINT, writerHandler);
    }
}

int main(){
    int i, j;
    int status = 0;
    pid_t wpid;
    int ShmID;
    int *ShmPTR;
    
    ShmID = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);

    for (i = 0; i < 3; i++){
        child_pid[i] = fork();
        switch(child_pid[i]){ /*switch(child_pid[i]){*/
            case -1:
                exit(EXIT_FAILURE);
            case 0: /* Child */
                //child_pid[i] = getpid();
                //do exec
                execvp("./sharedmemory_reader", NULL);
            default:
                break;
        }
    }

    if(signal(SIGINT, writerHandler) == SIG_ERR){
        printf("Binding signal handler writerHandler to SIGINT error!\n");
        exit(EXIT_FAILURE);
    }
    //Parent comes here; Send a signal to notify the children
    srand(time(NULL) + getpid());
    int number;
    sleep(3);
    while(1){
        sleep(1);

        if(handle_var){
            break;
        }

        number = (rand() % (MAX_VALUE+1-MIN_VALUE)) + MIN_VALUE;
        printf("Parent writer process generated number %d\n", number);

        ShmPTR = (int *) shmat(ShmID, NULL, 0);
        *ShmPTR = number;
        for( j = 0; j < 3; ++j){
            //printf("Sending signal to child %ld\n", (long)child_pid[j]);
            kill(child_pid[j], SIGUSR1);
        }
    }
    //kill all the children before
    
    
    //wait on all children before exiting
    printf("Wating on all the children to terminate...\n");
    while ((wpid = wait(&status)) > 0);
    
    /* detach shared memory segment */  
    shmdt(ShmPTR);  
    /* remove shared memory segment */  
    shmctl(ShmID, IPC_RMID, NULL);

    return 0;
}
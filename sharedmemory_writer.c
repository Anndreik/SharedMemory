#include "shm_header.h"

#define MAX_VALUE 1000
#define MIN_VALUE 2

int main(){
    int i, j;
    int status = 0;
    pid_t wpid;
    int ShmID;
    int *ShmPTR;
    ShmID = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);


    pid_t child_pid[3];
    for (i = 0; i < 3; i++){
        switch(fork()){
            case -1:
                exit(EXIT_FAILURE);
            case 0: /* Child */
                child_pid[i] = getpid();
                //do exec
                execvp("./sharedmemory_reader", NULL);
            default:
                break;
        }
    }

    //Parent comes here; Send a signal to notify the children
    srand(time(NULL) + getpid());
    int number;
    
    //while(1){
        printf("Parent: before sending signals to children\n");
        
        number = (rand() % (MAX_VALUE+1-MIN_VALUE)) + MIN_VALUE;
        printf("Parent generated number %d\n", number);
        ShmPTR = (int *) shmat(ShmID, NULL, 0);
        *ShmPTR = number;
        printf("Parent ------- Number in shared memory is %d\n", *ShmPTR);
        sleep(2);
        //printf("----------------------------------------------\n");
        for( j = 0; j < 3; ++j){
            //printf("Sending signal to child %ld\n", (long)child_pid[j]);
            kill(child_pid[j], SIGUSR1);
        }
    //}
    //wait on all children before exiting
    while ((wpid = wait(&status)) > 0);
    
    /* detach shared memory segment */  
    shmdt(ShmPTR);  
    /* remove shared memory segment */  
    shmctl(ShmID, IPC_RMID, NULL);

    return 0;
}
#include "shm_header.h"

int main(){
    int i;
    pid_t child_pid[3];
    for (i = 0; i < 3; i++){
        switch(fork()){
            case -1:
                exit(EXIT_FAILURE);
            case 0: /* Child */
                //do exec
            default:
                break;
        }
    }

    return 0;
}
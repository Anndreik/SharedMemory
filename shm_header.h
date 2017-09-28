//implement signal handler to use in the reader
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

#define SHM_KEY 0x1234 /* Key for shared memory segment */
#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
/* Permissions for our IPC objects */
// TODO: add the appropriate head files here

/************************************************************\
 * get_arguments - returns the command line arguments not
 *                 including this file in an array with the
 *                 last element as null.  This is the format
 *                 that the execvp() function requires.
 * 
 * For example:  ./time ls -l
 * will return an array consisting of {"ls","-l", NULL}
 ************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

double elapsed_time(struct timeval* start_time, struct timeval* end_time);

char** get_arguments(int argc, char** argv){
    int arg_length = argc;
    char**  cmd_args = NULL;

    if (arg_length > 0){
        cmd_args = (char**)malloc(sizeof(char*)*arg_length);
    }
    for(int i = 0; i < arg_length-1; i++){
        cmd_args[i] = argv[i+1];
    }
    cmd_args[arg_length-1] = NULL;
    return cmd_args;
}


int main(int argc, char** argv)
{
    pid_t pid;
    int status;
    char* command = NULL;
    char** command_args = NULL;
    char* ipc_ptr = NULL; // pointer to shared memory
    struct timeval start_time;
    struct timeval current_time;

    if (argc < 2){
        fprintf(stderr,"SYNOPSIS: %s <cmd> <cmd arguments>\n",argv[0]);
        return 1;
    }
    int shmid;

    shmid = shmget(IPC_PRIVATE, sizeof(struct timeval), IPC_CREAT |0666);
    if(shmid<0){
        perror("shmget");
        exit(1);
    }
    // TODO: call ipc_create to create shared memory region to which parent
    //       child have access.

    /* fork a child process */
    ipc_ptr = (char*) shmat(shmid, NULL, 0);
    if(ipc_ptr == (char*)-1){
        perror("shmat");
        exit(1);
    }
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork failed!");
        return 2;
    }
    else if (pid == 0) { /*child process */
        // TODO: use gettimeofday to log the start time

        // TODO: write the time to the IPC
        
        // TODO: get the list of arguments to be used in execvp() and 
        // execute execvp()
        gettimeofday(&start_time, NULL);
        *(struct timeval*) ipc_ptr = start_time;
        char** command_args = get_arguments(argc, argv);
        execvp(command_args[0], command_args);
        perror("execvp");
        exit(1);

    }
    else { /* parent process */
        // TODO: have parent wait and get status of child.
        //       Use the variable status to store status of child. 
        
        // TODO: get the current time using gettimeofday
        
        // TODO: read the start time from IPC
        
        // TODO: close IPC

        // NOTE: DO NOT ALTER THE LINE BELOW.
        wait(&status);
        gettimeofday(&current_time, NULL);
        start_time = *(struct timeval*) ipc_ptr;
        shmdt(ipc_ptr);
        shmctl(shmid, IPC_RMID, NULL);
        printf("Elapsed time %.5f\n",elapsed_time(&start_time, &current_time));
    }
    
    
    return status;

}
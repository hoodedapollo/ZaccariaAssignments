#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "pointC_lib.h"


int main (int argc, char *argv[]) {
        int fildes_firstpipe[2];                                      // declaration of the file descriptors array    
        int fildes_secondpipe[2];
        char firstpipe_fd0[20], firstpipe_fd1[20];                    // declaration of the corrispective char array in order to pass 
        char secondpipe_fd0[20], secondpipe_fd1[20];
        pid_t fork_pid_child2;
        int firstpipe_ret, secondpipe_ret;

        FILE *f = fopen("pointC.log", "w");  // clear the log file at each execution of the process
        fclose(f);

        firstpipe_ret = pipe(fildes_firstpipe); // here the pipe is created and the file descriptors are passed to fildes
        log_func("FATHER first pipe");
        err_control(firstpipe_ret,"FATHER first pipe: ",0);

        secondpipe_ret = pipe(fildes_secondpipe);
        log_func("FATHER second pipe");
        err_control(secondpipe_ret,"FATHER second pipe: ",0);

        sprintf(firstpipe_fd0,"%d", fildes_firstpipe[0]);                  // file descriptors are converted to array
        sprintf(firstpipe_fd1,"%d", fildes_firstpipe[1]);                  // of chars in odrder to passa them to char **argv
        sprintf(secondpipe_fd0,"%d", fildes_secondpipe[0]);                  // file descriptors are converted to array
        sprintf(secondpipe_fd1,"%d", fildes_secondpipe[1]);                  // of chars in odrder to passa them to char **argv

        argv[1] = firstpipe_fd0;                             // putting the char format file descriptors in the pointer to array of char (char **argv) 
        argv[2] = firstpipe_fd1;                             // by definition the last member must be NULL 
        argv[3] = secondpipe_fd0;
        argv[4] = secondpipe_fd1; 
        argv[5] = NULL;

        pid_t fork_pid_child1 = fork();                            // a child process is created through forking
        if (fork_pid_child1 != 0)  // father process
        {
                log_func("FATHER first fork");
                err_control(fork_pid_child1,"FATHER first fork: ",0);
                fork_pid_child2 = fork();
        }

        if (fork_pid_child1 == 0)  // child1 process code
        {                               
                argv[0] = "child1";                         // by definition the first element must be the bin namefile
                int exec_child1_ret = execve("child1", argv, NULL);               //  
                err_control(exec_child1_ret,"FATHER child1 exec: ",0);
        }
        else if (fork_pid_child2 != 0) // father process
        {
                log_func("FATHER second fork");
                err_control(fork_pid_child1,"FATHER second fork: ",0);
        }

        else if (fork_pid_child2 == 0)  // child2 process
        {
                argv[0] = "child2";
                int exec_child2_ret = execve("child2", argv, NULL);
                err_control(exec_child2_ret,"FATHER child2 exec: ",0);
        }

        if (fork_pid_child1 != 0 && fork_pid_child2 != 0)  // father process
        {
                int first_wait_ret = wait(NULL);  // wait for one of the children
                log_func("FATHER first wait");
                err_control(first_wait_ret,"FATHER first wait: ",0);

                int second_wait_ret = wait(NULL);  // wait for the other children
                log_func("FATHER second wait");
                err_control(second_wait_ret,"FATHER second wait: ",0);

                return 0;
        }     
}

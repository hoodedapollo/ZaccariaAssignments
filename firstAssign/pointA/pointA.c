#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "pointA_lib.h"

int main(int argc, char *argv[]) 
{

        FILE *f =fopen("pointA.log","w");  // clear the log file
        fclose(f);

        pid_t fork_pid = fork();
        if (fork_pid != 0)  // father process
        {
                log_func("FATHER first fork");  // write in the log file 
                err_control(fork_pid,"FATHER fork: ",0); // if error occurs print it to stdout and return -1
                pid_t pid_from_wait = wait(NULL);  // wait for the child to exit
                log_func("FATHER wait");
                err_control(pid_from_wait,"FATHER wait: ",0);
                if (pid_from_wait == fork_pid) 
                {
                        printf("\nDamn you, you left my son to die\n"); fflush(stdout);
                }
        }

        if (fork_pid == 0)  // child process
        {
                printf("\nHi I'm the child process.\nPlease help me, I don't want to die\n"); fflush(stdout);
                sleep(2);
                for (int i = 0;i<3;i++)
                {
                        printf("\nHeeeeeeeelp\n"); fflush(stdout);
                        sleep(1);
                }

                exit(EXIT_SUCCESS); 

        }
        return 0;
}

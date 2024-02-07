
#include <stdio.h>
#include <stdlib.h>   // exit
#include <sys/wait.h> // wait
#include <unistd.h>   // fork
#include <signal.h>

int main()
{    
    int rc, status, pid;
    rc = fork();

    if(rc < 0)        //Failed fork
    {
        fprintf(stderr, "Failed to fork\n");
        
    } else if(rc == 0){    //Child process
        
        int p = wait(NULL);
        printf("Hello from child (%d), p = %d\n", p);
        exit(0);
    }
    else{                    //Parent process
        pid = wait(&status); 
        if(WIFEXITED(status)){
            printf("Normal termination of child (%d), exit status = %d\n", pid, WEXITSTATUS(status));
        }
        printf("Goodbye from parent (%d)\n", getpid());
    }
}


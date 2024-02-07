
#include <stdio.h>
#include <stdlib.h>   // exit
#include <sys/wait.h> // wait
#include <unistd.h>   // fork


int main()
{
    int rc, status, pid;
    rc = fork();

    if(rc < 0)        //Failed fork
    {
        
        printf("Failed to fork\n");
    
    }else if(rc == 0)   //Child process
    {
        
        close(STDOUT_FILENO);
        printf("Child (%d) print to stdandard output.\n", getpid());
        exit(0);
        
    }
    else{                //Parent process
        
        printf("Goodbye from parent (%d)\n", getpid());
    
    }
}

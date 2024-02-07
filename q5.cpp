
#include <stdio.h>
#include <stdlib.h>   // exit
#include <sys/wait.h> // wait
#include <unistd.h>   // fork


int main()
{
    int rc, status, pid;
    rc = fork();

    if(rc < 0)        //Error fork
    {
        
        printf("failed to fork\n");
    
    }else if(rc == 0){        //Child process
        
        printf("Hello from child (%d)\n", getpid());
        exit(0);
        
    }else{                    //Parent process
        
        pid = waitpid(rc, &status, 0); 
        if(WIFEXITED(status))
        {
            printf("normal termination of child (%d), exit status = %d\n", pid, WEXITSTATUS(status));
        }
            printf("Goodbye from parent (%d)\n", getpid());
    }
    return 0;
}

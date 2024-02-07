#include <stdio.h>
#include <stdlib.h>   // exit
#include <sys/wait.h> // wait
#include <unistd.h>   // fork

int main(){
    int rc;

    //For execl
    rc = fork();
    char * args[] = {"ls", "-l", NULL};
    char * env[] = {NULL};

    if(rc < 0)        //Error occurred
    {
        fprintf(stderr, "Failed to fork\n");
        exit(EXIT_FAILURE);
    }
    else if(rc == 0){    //Child process
        
        execl("/bin/ls", "ls", "-l", NULL);  //using execl
        
        //execv("/bin/ls", args);
        //execle("/bin/ls", "ls", "-l", (char *) 0, env);
        //execve("/bin/ls", args, env);
        //execlp("ls", "ls", "-l", (char *) 0);

        perror("execl");
        exit(EXIT_FAILURE);
        
    } else {                //Parent
        
        sleep(1);
        printf("Goodbye from parent\n");
        
    }

    return 0;
}

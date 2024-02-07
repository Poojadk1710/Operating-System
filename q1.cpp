#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    
    int x;
    x = 100;
    int rc = fork();
    
    if(rc < 0)                    //Error
    {
        
        fprintf(stderr, "Failed to fork\n"); 
        
    }
    else if(rc == 0){             //Child process

        printf("Child process\n");
        printf("The Current value of X: %d\n", x);
        x = 99;
        printf("Child process will now get x as : %d\n", x);
        
        
    }else{                        //Parent process

        wait(NULL);
        printf("Parent process\n");
        printf("The Current value of X: %d\n", x);
        x = 101;
        printf("Parent process will now be set x to : %d\n", x);
    
    }

    return 0;
}

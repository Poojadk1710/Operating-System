#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    int fd, rc;
    fd = open("output.txt", O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd < 0) 
    {
     
        perror("Open");
        exit(EXIT_FAILURE);
        
    }

    char buf1[] = "File 1\n";
    char buf2[] = "File 2\n";
    
    rc = fork();
    if(rc < 0)            //Failed fork
    {
        
        printf("Failed to fork\n");
    
    } else if(rc == 0)     //Child process
    {
        const char * child_msg = "Hey, This is child process\n";
        printf("The child process is writing on the file\n");
        write(fd, buf1, sizeof(buf1) - 1);     //removes '\0'
        exit(0);
        
    } else {                //Parent process
        
        wait(NULL); // Wait for the child process to finish
        const char * child_msg = "Hey, This is parent process\n";
        printf("The parent process is writing on the file\n");
        write(fd, buf2, sizeof(buf2) - 1); //remove '\0'
    
    }

    close(fd); // Close the file descriptor
    return 0;
}

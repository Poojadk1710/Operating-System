#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


#define MAXLINE 1024

int main() 
{
    int fd[2];
    pid_t pid1, pid2;
    char line[MAXLINE];

    if (pipe(fd) < 0) {        //Error
        perror("Pipe error");
        exit(EXIT_FAILURE);
    }

    if ((pid1 = fork()) < 0)
    {    //Fork error
        perror("Fork error");
        exit(EXIT_FAILURE);
        
    } else if (pid1 == 0) {
        // Child process 1
        
        close(fd[0]);  // Close read end of the pipe

        // Redirect stdout to the write end of the pipe
        
        if (dup2(fd[1], STDOUT_FILENO) < 0) {
            perror("dup2 error");
            exit(EXIT_FAILURE);
        }

        // Execute a command (e.g., echo) to write to the pipe
        printf("hello from child process 1\n");

        exit(EXIT_SUCCESS);
    }

    if ((pid2 = fork()) < 0) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // Child process 2
        close(fd[1]);  // Close write end of the pipe

        // Redirect stdin to the read end of the pipe
        if (dup2(fd[0], STDIN_FILENO) < 0) {
            perror("dup2 error");
            exit(EXIT_FAILURE);
        }

        // Read from stdin (which is now connected to the pipe)
        ssize_t n = read(STDIN_FILENO, line, MAXLINE);
        if (n < 0) {
            perror("read error");
            exit(EXIT_FAILURE);
        }

        // Write to stdout to demonstrate the received message
        write(STDOUT_FILENO, line, n);

        exit(EXIT_SUCCESS);
    }

    // Parent process
    close(fd[0]);
    close(fd[1]);

    // Wait for both child processes to terminate
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

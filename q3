#include <stdio.h>
#include <stdlib.h>   // exit
#include <sys/wait.h> // wait
#include <unistd.h>   // fork

int main() {
  int rc;
  rc = fork();
  char *args[] = {"ls", "-1", NULL};
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");     // fork failed; exit
    exit(EXIT_FAILURE);
  } else if (rc == 0) {
    //child process
   execvp("ls",args); //If execvp returns it means there an error 
    perror("execvp");
    exit(EXIT_FAILURE);
  } else {
    wait(NULL); //Wait for the child process to finish
    printf("Child process finished executing");
  }
  return 0;
}

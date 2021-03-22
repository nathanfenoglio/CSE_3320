#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
 
void childTask() {
    printf("Hello World\n");
    printf("getpid(): %d\n", getpid());

}
 
void parentTask() {
  printf("Main task.\n");
  printf("getpid(): %d\n", getpid());
}
 
int main(void) {
  pid_t pid = fork();
  printf("getpid(): %d\n", getpid());

  if(pid == 0) {
    printf("getpid(): %d\n", getpid());

    childTask();
    exit(EXIT_SUCCESS);
  }
  else if(pid > 0) {
    wait(NULL);
    parentTask();
  }
  else {
    printf("Unable to create child process.");
  }
 
  return EXIT_SUCCESS;
}
//this code is not working and I think it has to do with the void pointer business...
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> //this header gets rid of the warning: implicit declaration of function ‘wait’; did you mean ‘main’?
#include <unistd.h>

int main(int argc, char **argv){
    void *status; //what is this exactly? a void pointer I know can be any type and then is cast when you are actually going to do something with it
    int childpid;

    //now create new process
    childpid = fork();
    char *const parmList[] = {"./Helloworld", NULL};

    if(childpid == 0){ //fork() returns 0 to the child process
        sleep(1);
        printf("CHILD: My parent's PID: %d\n", getppid());
        //why does he have the below line commented out? Looks like it is the command to execute the executable
        //execve("./helloworld, parmList");
        exit(1);
    }
    else{ //fork() returns new pid to the parent process
        printf("PARENT: my child PID: %d\n", childpid);
        wait(&status); //so what does status contain at this point? All I see is that it was declared a void pointer so far...
        printf("PARENT: Child's exit code is: %d\n", WEXITSTATUS(status));
        exit(0);
    }
}


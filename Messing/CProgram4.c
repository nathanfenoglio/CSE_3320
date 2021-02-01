#include <stdio.h>
#include <unistd.h>

int main(){
    int proc_id, par_proc_id;
    proc_id = getpid();
    par_proc_id = getppid();

    printf("PROCESS ID: %d\n", proc_id);
    printf("PARENT PROCESS ID: %d\n", par_proc_id);
    
}
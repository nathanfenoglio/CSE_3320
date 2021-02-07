#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/utsname.h>

int main(){
    struct utsname buff;

    errno = 0;
    if(uname(&buff) != 0){
        perror("uname doesn't return 0, so there is an error\n");
        exit(EXIT_FAILURE);
    }

    printf("System Name = %s\n", buff.sysname);
    printf("Node Name = %s\n", buff.nodename);
    printf("Release Name = %s\n", buff.release);
    printf("Version Name = %s\n", buff.version);
    printf("Machine Name = %s\n", buff.machine);

    //stopped at 1:50
}
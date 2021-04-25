#include <unistd.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_virt_address_status 339

int main(int argc, char **argv)
{
        int pid;
        unsigned long virt_mem_address;

        printf("Enter the process id to find:\n");
        scanf("%d", &pid);

        printf("Enter the virtual memory address:\n");
        scanf("%ld", &virt_mem_address);

        int ret = syscall(__NR_virt_address_status, virt_mem_address, pid);
        printf("%d\n", ret);

        return 0;
}

Nathaniel Fenoglio 1001634050
Lemuel Rivera 1000842851

**************************************************
Files included:
Project3Report.docx

Makefile (modified version to include new system calls for top level kernel directory)

syscall_64.tbl (modified version to include new system calls for location ~/linux-4.14.217/arch/x86/entry/syscalls)

syscalls.h (modified version to include new system calls for location ~/linux-4.14.217/include/linux)

user_space_source/test_virt_address_stats.c
user_space_source/test_virt_address_stats_threads.c
user_space_source/test_virt_address_status.c

my_source/Makefile
my_source/sys_virt_address_stats.c
my_source/sys_virt_address_status.c

**************************************************

Part 1
test_virt_address_stats.c
takes user input for process id then prints out virtual memory information of the process
program mimics output of pmap terminal command

test_virt_address_stats_threads.c
prints out virtual memory information for 4 threads 
that should all print out the same information since threads share the same memory address space of the process that they exist within

Part 2
test_virt_address_status.c
takes user input for process id and virtual memory address and outputs 
if the data is in memory or on disk (Present flag value)
if the page that the memory belongs to has been referenced (Referenced flag value)
if the page is dirty (modified since last write) (Dirty flag value)

**************************************************
Compilation instructions:
to be built in a linux os
the specific linux kernel version used is linux-4.14.217

copy Makefile (for top level directory) to ~/linux-4.14.217/
cp Makefile ~/linux-4.14.217/

copy syscall_64.tbl file to ~/linux-4.14.217/arch/x86/entry/syscalls
cp syscall_64.tbl ~/linux-4.14.217/arch/x86/entry/syscalls

copy syscalls.h file to ~/linux-4.14.217/include/linux
cp syscalls.h ~/linux-4.14.217/include/linux

put user_space_source directory anywhere in user space or leave where it, by default, is if ok

copy directory my_source to top level of kernel directory
cp my_source ~/linux-4.14.217/ -r

Part 1
open 2 terminals, in one terminal cd /proc, ls to see valid process ids, 
pmap [process_id_#] to check that a process has memory information
gcc -o test_virt_address_stats test_virt_address_stats.c
./test_virt_address_stats
Enter a process id to see virtual memory details for: [process_id_#]
enter command "dmesg" to see output printed by kernel

gcc -o test_virt_address_stats_threads test_virt_address_stats_threads.c -lpthread
./test_virt_address_stats_threads
enter command "dmesg" to see output printed by kernel

Part 2
gcc -o test_virt_address_status test_virt_address_status.c
./test_virt_address_status
Enter the process id to find: [process_id_#]
Select virtual memory address input type (1 or 0)
	hexadecimal - 1
	decimal - 0
Enter the virtual memory address: [enter memory address in hexadecimal or decimal according to what was selected for previous choice]
enter command "dmesg" to see output printed by kernel

**************************************************



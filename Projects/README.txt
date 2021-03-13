Nathaniel Fenoglio 1001634050
Lemuel Rivera 1000842851

**************************************************

Files included:
Project1Report.docx

Makefile (modified version to include new system calls for top level kernel directory)
syscall_64.tbl (modified version to include new system calls for location ~/linux-4.14.217/arch/x86/entry/syscalls)
syscalls.h (modified version to include new system calls for location ~/linux-4.14.217/include/linux)

user_space_source/test_syscall.c
user_space_source/test_print_self.c
user_space_source/test_print_other.c

my_source/Makefile
my_source/sys_helloworld.c
my_source/sys_print_self.c
my_source/sys_print_other.c

**************************************************
test_syscall.c uses function syscall to call newly registered system call 333 and prints "Hello World !" as a kernel message viewable by entering the command "dmesg"

test_print_self.c calls newly registered system call 334 which prints the various information about the current process 
and prints the parent processes of the current process up to the initial process

test_print_other.c calls newly registered system call 335 which accepts a command line argument for a process id to search for
if found, various information about the specified process is printed out as a kernel message viewable by entering the command "dmesg"

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

compile and run test_syscall.c
gcc -o test_syscall test_syscall.c
./test_syscall

enter command "dmesg" to see output printed by kernel

compile and run test_print_self.c
gcc -o test_print_self test_print_self.c 
./test_print_self

enter command "dmesg" to see output printed by kernel

compile and run test_print_other.c
this program takes in a command line argument of the process id # that will be searched for
process id 10 is used in the example, but could be any process id
can enter "top" in terminal to view a list of running processes and their process ids for reference
gcc -o test_print_other test_print_other.c
./test_print_other 10

enter command "dmesg" to see output printed by kernel

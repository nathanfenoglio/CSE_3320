#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

/*
sbuf has this structure:
struct  stat {
        time_t    st_atime;     // time of last access       
        time_t    st_ctime;     // time of file's creation   
        dev_t     st_dev;       // The drive number (0 = a:) 
        gid_t     st_gid;       // what getgid() returns 
        ino_t     st_ino;       // starting cluster or unique identifier 
        mode_t    st_mode;      // file mode - S_IF* and S_IRUSR/S_IWUSR
        time_t    st_mtime;     // time that the file was last written 
        nlink_t   st_nlink;     // 2 + number of subdirs, or 1 for files 
        off_t     st_size;      // size of file in bytes 
        blksize_t st_blksize;   // block size in bytes
        uid_t     st_uid;       // what getuid() returns 
	    dev_t     st_rdev;      // The drive number (0 = a:) 
};
*/
int main(int argc, char **argv){
    int fd, offset;
    char *data;
    struct stat sbuf; //see above for sbuf struct members

    if(argc != 2){
        fprintf(stderr, "usage: mmapdemo offset\n");
        exit(1);
    }

    if((fd = open("flam4.txt", O_RDONLY)) == -1){
        perror("open\n");
        exit(1);
    }

    if(stat("flam4.txt", &sbuf) == -1){
        perror("stat\n");
        exit(1);
    }

    offset = atoi(argv[1]);
    //sbuf.st_size - st_size is member of sbuf struct 
    //size of file in bytes
    if(offset < 0 || offset > sbuf.st_size - 1){
        fprintf(stderr, "mmapdemo: offset must be in the range 0-%d\n", sbuf.st_size - 1);
        exit(1);
    }

    //https://man7.org/linux/man-pages/man2/mmap.2.html
    /*
        #include <sys/mman.h>

       void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);
       int munmap(void *addr, size_t length);

    */
    //mmap does away with the read and write system calls like in the while loop of copyfile.c
    //so faster, does away with 2 microsecond transitions from user space into the kernel for each read or write system call
    //mmap also does away with the need for memory for an intermediate buffer
    data = mmap((caddr_t)0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);   
    if(data == (caddr_t)(-1)){
        perror("mmap\n");
        exit(1);
    }

    printf("byte at offset %d is '%c'\n", offset, data[offset]);

    return 0;
}

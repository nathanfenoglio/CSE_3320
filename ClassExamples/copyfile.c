#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUF_SIZE 4096 //use a buffer size of 4096 bytes
#define OUTPUT_MODE 0700 //protection bits for output file
#define TRUE 1

int main(int argc, char **argv){
    int in_fd, out_fd, rd_count, wt_count;
    char buffer[BUF_SIZE];

    //syntax error if argc is not 3, should take 2 arguments: input file and output file
    if(argc != 3){ 
        printf("not enough args, need input file and output file\n");
        exit(1);
    }

    //open the input file and create the output file
    in_fd = open(argv[1], O_RDONLY);
    printf("in_fd: %d\n", in_fd); //just printing
    if(in_fd < 0){
        exit(2);
    }

    out_fd = creat(argv[2], OUTPUT_MODE); //the example had create instead of creat
    printf("in_fd: %d\n", in_fd); //just printing
    if(out_fd < 0){
        exit(3);
    }

    //copy loop
    while(TRUE){
        rd_count = read(in_fd, buffer, BUF_SIZE); //read a block of data
        printf("rd_count: %d\n", rd_count); //just printing

        if(rd_count <=0){
            break;
        }
        wt_count = write(out_fd, buffer, rd_count); //rd_count returns # of bytes read
        if(wt_count <= 0){
            exit(4);
        }
    }

    //close the files
    close(in_fd);
    close(out_fd);

    if(rd_count == 0){ //no error on last read
        exit(0);
    }
    else{ //error on last read
        exit(5);
    }
}
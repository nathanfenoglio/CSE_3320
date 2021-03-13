#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    clock_t start_t, end_t, total_t;
    int i;

    start_t = clock();
    printf("at the start of the program, start_t = %ld\n", start_t);

    printf("going to start a big loop, start_t is %ld\n", start_t);

    for(i = 0; i < 10000000; i++){
        printf("flam");
    }
    printf("\n");

    end_t = clock();
    printf("at the end of doing the big loop, end_t is %ld\n", end_t);

    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    //total_t = (double)(end_t - start_t);
    printf("Total time taken by the CPU: %li\n", total_t);
    printf("Exiting the program...\n");

    return(0);

}


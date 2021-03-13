//Compile and link with -pthread
//code not working there may be stuff not shown such as how does main know about tid
//when is a declared? etc.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NR_THREADS 4

void* my_thread(void *arg){
    int *tid = (int *)arg;
    printf("Hello from child thread: %d\n");
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t threads[NR_THREADS];
    int i;
    for(i = 1; i < NR_THREADS; i++){
        tid[i] = i;
        pthread_create(&threads[i], &a, my_thread, &tid[i]);
    }

    printf("Hello from the mother thread 0 !\n");

    for(i = 1; i < NR_THREADS; ++i){
        pthread_join(threads[i], NULL);
    }

    return 0;
}
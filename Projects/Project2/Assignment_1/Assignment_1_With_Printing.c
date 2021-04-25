#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MAX 1024
#define NUM_THREADS 4

//need to protect access to this global total so that different threads do not access at the same time
int total = 0; 

int n1, n2;
char *s1, *s2;
FILE *fp;

int section_length = 0; //global variable for how large of a section each of the threads will work on 

pthread_t threads[NUM_THREADS];
pthread_mutex_t the_mutex;

int readf(FILE *fp){
    if((fp = fopen("strings.txt", "r")) == NULL){
        printf("ERROR: can't open string.txt!\n");
        return 0;
    }

    s1 = (char *)malloc(MAX * sizeof(char));
    if(s1 == NULL){
        printf("ERROR: Out of memory!\n");
        return -1;
    }

    s2 = (char *)malloc(MAX * sizeof(char));
    if(s2 == NULL){
        printf("ERROR: Out of memory\n");
        return -1;
    }

    //read s1 s2 from the file
    s1 = fgets(s1, MAX, fp);
    s2 = fgets(s2, MAX, fp);

    //remove '\r' or '\n' from strings
    int i;
    for(i = 0; i < strlen(s1); i++){
        if((s1[i] == '\r') || (s1[i] == '\n')){
            s1[i] = '\0';
            break;
        }
    }

    for(i = 0; i < strlen(s2); i++){
        if((s2[i] == '\r') || (s2[i] == '\n')){
            s2[i] = '\0';
            break;
        }
    }

    n1 = strlen(s1); //length of string 1
    n2 = strlen(s2); //length of string 2

    //check if either string is NULL or if the string that we are searching is smaller than the string that we are trying to match
    if(s1 == NULL || s2 == NULL || n1 < n2){
        return -1;
    }
}

void * num_substring(void *start_offset){
    int start = *((int *)start_offset);
    printf("start: %d\n", start);

    int i, j, k;
    int count;
    
    for(i = start; i < start + section_length; i++){
        count = 0;
        for(j = i, k = 0; k < n2; j++, k++){ //search for the next string of size of n2
            if(*(s1 + j) != *(s2 + k)){
                break;
            }
            else{
                count++;
                //just printing
                printf("i: %d, j: %d, count: %d\n", i, j, count);
            }

            //if updating global total variable, 
            //need to lock mutex to only allow update to come from one thread at a time
            if(count == n2){
                pthread_mutex_lock(&the_mutex);
                total++; 
                pthread_mutex_unlock(&the_mutex);
            }
        }
    }

}

int main(int argc, char **argv){
    pthread_attr_t attr;

    readf(fp);

    //n1 and n2 have already been updated by readf function and have the string sizes
    printf("n1: %d, n2: %d\n", n1, n2);
    section_length = n1 / NUM_THREADS;
    printf("n1modNUM_THREADS: %d\n", n1%NUM_THREADS);

    //divide up what is leftover amongst the available threads 
    //and add nearest whole # amount to section_length in order to cover strings that don't divide evenly
    if((n1 % NUM_THREADS) != 0){
        section_length = section_length + ((n1 % NUM_THREADS) / NUM_THREADS) + 1;
    }

    //just printing
    printf("section_length: %d\n", section_length);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int offsets_per_thread[NUM_THREADS];
    int i;
    for(i = 0; i < NUM_THREADS; i++){
        //need to store the different offsets in separate locations in the array 
        //one offset variable caused random problems due to the value being seen at different times by the different threads
        offsets_per_thread[i] = i * section_length;
        pthread_create(&threads[i], &attr, num_substring, (void *) &offsets_per_thread[i]);

    }
    pthread_attr_destroy(&attr);
    
    for(i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&the_mutex);
    printf("The number of substrings is: %d\n", total);
    pthread_exit(NULL);
    return 1;
}

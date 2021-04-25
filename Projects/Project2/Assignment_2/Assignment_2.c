#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5 //Size of the buffer

/* The mutex lock */
pthread_mutex_t mutex;

/* the semaphores */
sem_t full, empty;

pthread_attr_t attr;

pthread_t the_producer;
pthread_t the_consumer;

char buffer[BUFFER_SIZE];

int buffer_count = 0; //keep track of how many characters are in buffer, so as not to overwrite characters not yet printed by consumer thread
int in = 0; //for producer to keep track of where to write in buffer
int out = 0; //for consumer to keep track of where to read in buffer

void * producer(void *param){
    FILE *the_file;
    the_file = fopen("message.txt", "r");
    if(the_file == NULL){
        perror("Failed to open file ");
    }


    char one_char;
    
    while(1){
        //consumer thread posts on empty semaphore when done in critical region 
        //after unlocking mutex, so will wake up producer who is waiting on it
        sem_wait(&empty); 
        //acquire mutex to enter critical region to write in buffer
        pthread_mutex_lock(&mutex); 
        
        //get character from file
        one_char = fgetc(the_file);

        //check if buffer is less than full
        if(buffer_count < BUFFER_SIZE){
            buffer[in] = one_char;
            //increment index of buffer to insert next character into 
            //wraps back around to beginning of buffer
            //checking buffer count takes care of making sure no character is overwritten before the consumer consumes
            in = (in + 1) % BUFFER_SIZE; 
            //increment buffer_count one closer to max BUFFER_SIZE
            buffer_count++;

            //check if character read is end of file in order to exit
            if(one_char == EOF){
                break;
            }
        }

        pthread_mutex_unlock(&mutex); //unlock mutex, outside of critical region
        sem_post(&full); //signal consumer thread who waits on full semaphore to wake up
    }
    
    fclose(the_file);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void * consumer(void *param){
    while(1){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        if(buffer_count > 0){
            //check if last entry in buffer from producer was end of file
            if(buffer[out] == EOF){
                printf("\n");
                break;
            }

            printf("%c", buffer[out]);
            out = (out + 1) % BUFFER_SIZE; //increment next read position
            buffer_count--; //decrease buffer count signifying space for another character to be produced safely
        }

        pthread_mutex_unlock(&mutex); //unlock mutex, outside of critical region
        sem_post(&empty); //signal producer thread who waits on empty semaphore to wake up

    }

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}

int main(int argc, char **argv){
    pthread_mutex_init(&mutex, NULL);

     /* Create the full semaphore and initialize to 0 */
    sem_init(&full, 0, 0);

    /* Create the empty semaphore and initialize to BUFFER_SIZE */
    sem_init(&empty, 0, BUFFER_SIZE);

    /* Get the default attributes */
    pthread_attr_init(&attr);

    /* init buffer */
    buffer_count = 0;

    pthread_create(&the_producer, &attr, producer, NULL);
    pthread_create(&the_consumer, &attr, consumer, NULL);
    

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    pthread_exit(NULL);
}   

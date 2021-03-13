#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_THREADS 4

struct thread_data{
   int tid;
   int sum;
   char *blah_blah;
};


void * thread_main(void *arg)
{
	struct thread_data *thread_data;
	thread_data = (struct thread_data *)arg;
	printf("Hello World! It's me, thread #%d and my sum is %d\n", thread_data->tid, thread_data->sum);
	printf("%s\n", thread_data->blah_blah);
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc, i, sum=0;
	struct thread_data thread_data_array[NUM_THREADS];
	//just some words for the various threads
	char *thread_words[4] = {"", "butt", "flim", "flam"};
	thread_words[0] = "fart bucket mcgee";
	for(i=0; i<NUM_THREADS; i++){
		sum = sum + i;
		thread_data_array[i].tid = i;
		thread_data_array[i].sum = sum;
		thread_data_array[i].blah_blah = thread_words[i];
		rc = pthread_create(&threads[i], NULL, thread_main, (void *) &thread_data_array[i]);
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	/* Last thing that main() should do */
	pthread_exit(NULL);
}

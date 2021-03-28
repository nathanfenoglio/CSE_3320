#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NUM_THREADS	4
#define EXCLUDED_THREAD 2

//not sure why static, doesn't seem to be necessary...
static pthread_barrier_t b;

void *BusyWork(void *t)
{
   int i;
   long tid;
   double result=0.0;
   tid = (long)t;
   srandom((unsigned int) time(NULL));
   int rand = random() % 10;
   for (i=0; i<1000000*rand; i++)
   {
      result = result + sin(i) * tan(i);
   }
   printf("Thread %ld has done phase 1. Result = %e\n",tid, result);
   //if (tid !=1) //needed to ditch this line in order to have the execution not get hung up here. But seems like he was meaning to use this to exclude one of the threads, wonder why it gets hung up???
   //if you omit pthread_barrier_wait the 2 phases complete here and there for the various threads
   //if you include all of the thread's phase 1 completes in random order, then all of thread's phase 2 completes 
   //pthread_barrier_wait(&b);
   if(tid != EXCLUDED_THREAD){
      pthread_barrier_wait(&b);
   }
   for (i=0; i<100; i++)
   {
      result = result + sin(i) * tan(i);
   }
   printf("Thread %ld has done phase 2. Result = %e\n",tid, result);
   pthread_exit((void*) t);
}

int main (int argc, char *argv[])
{
   pthread_t thread[NUM_THREADS];
   pthread_attr_t attr;
   int rc;
   long t;
   void *status;

   /* Initialize and set thread detached attribute */
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); //make threads detachable
   //pthread_barrier_init(&b, NULL, NUM_THREADS);
   //need to make sure to match the # of threads using the barrier to the # of threads used to initialize the barrier or it will get hung up
   pthread_barrier_init(&b, NULL, NUM_THREADS - 1); //-1 to not include the excluded thread, else it gets hung up

   for(t=0; t<NUM_THREADS; t++) {
      printf("Main: creating thread %ld\n", t);
      rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t); 
      if (rc) {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
         }
      }

   /* Free attribute and wait for the other threads */
   pthread_attr_destroy(&attr);
#if 1
   for(t=0; t<NUM_THREADS; t++) {
      
      if(t != EXCLUDED_THREAD){
         rc = pthread_join(thread[t], &status);
         if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
         }
//      printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
      }

      }
#endif
printf("Main: program completed. Exiting.\n");
pthread_exit(NULL);
}

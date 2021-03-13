#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define NUM_THREADS	4

//int result = 0; //if you declare result globally you get whatever funky result based on how the parallel threads go about there business

void *BusyWork0(void *t)
{
   int i;
   long tid;
   //double result=0.0;
   int result = 0;
   tid = (long)t;
   printf("Thread %ld starting...\n",tid);
   for (i=0; i<1000000; i++)
   {
      //result = result + sin(i) * tan(i);
      /*
      if(i < pow(tid, 7)){
         result = result + 1;
         //printf("%d", result);
      }
      */
     result = result + 1;
      
   }
   //printf("Thread %ld done. Result = %e\n",tid, result);
   printf("Thread %ld done. Result = %d\n",tid, result);
   pthread_exit((void*) t);
}

void *BusyWork1(void *t)
{
   int i;
   long tid;
   //double result=0.0;
   int result = 0;
   tid = (long)t;
   printf("Thread %ld starting...\n",tid);
   for (i=0; i<1000000; i++)
   {
      //result = result + sin(i) * tan(i);
      /*
      if(i < pow(tid, 7)){
         result = result + 1;
         //printf("%d", result);
      }
      */
     result = result + 2;
      
   }
   //printf("Thread %ld done. Result = %e\n",tid, result);
   printf("Thread %ld done. Result = %d\n",tid, result);
   pthread_exit((void*) t);
}

void *BusyWork2(void *t)
{
   int i;
   long tid;
   //double result=0.0;
   int result = 0;
   tid = (long)t;
   printf("Thread %ld starting...\n",tid);
   for (i=0; i<1000000; i++)
   {
      //result = result + sin(i) * tan(i);
      if(i < pow(tid, 7)){
         result = result + 1;
         //printf("%d", result);
      }
      
   }
   //printf("Thread %ld done. Result = %e\n",tid, result);
   printf("Thread %ld done. Result = %d\n",tid, result);
   pthread_exit((void*) t);
}

void *BusyWork3(void *t)
{
   int i;
   long tid;
   //double result=0.0;
   int result = 0;
   tid = (long)t;
   printf("Thread %ld starting...\n",tid);
   for (i=0; i<1000000; i++)
   {
      //result = result + sin(i) * tan(i);
      if(i < pow(tid, 7)){
         result = result + 1;
         //printf("%d", result);
      }
      
   }
   //printf("Thread %ld done. Result = %e\n",tid, result);
   printf("Thread %ld done. Result = %d\n",tid, result);
   pthread_exit((void*) t);
}

int main (int argc, char *argv[])
{
   pthread_t thread[NUM_THREADS];
   pthread_attr_t attr;
   int rc;
   long t;
   void *status;
   int thread_to_detach = 666;

   //create array of function pointers for each respective thread to use
   void (*fun_ptr0) = &BusyWork0;
   void (*fun_ptr1) = &BusyWork1;
   void (*fun_ptr2) = &BusyWork2;
   void (*fun_ptr3) = &BusyWork3;
   void (*func_ptrs[4]) = {fun_ptr0, fun_ptr1, fun_ptr2, fun_ptr3}; 
   /* Initialize and set thread detached attribute */
   //needed in order for thread to be detachable and is passed into pthread_create to make it so
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   for(t=0; t<NUM_THREADS; t++) {
      printf("Main: creating thread %ld\n", t);
      //rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t);
      rc = pthread_create(&thread[t], &attr, func_ptrs[t], (void *)t); 
//if you don't do below pthread_detach for thread 1, then everything joins up at the end 
//if you do do below pthread_detach for thread 1, then you have an error from trying to join thread 1 and the program exits
//maybe try to exclude joining thread 1 in the for loop...yea, that worked think he prob should have done the same 
#if 1
      if (t == thread_to_detach)
	      pthread_detach(thread[t]);
#endif
      if (rc) {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   /* Free attribute and wait for the other threads */
   pthread_attr_destroy(&attr);
#if 1
   for(t=0; t<NUM_THREADS; t++) {
      if(t != thread_to_detach){
         rc = pthread_join(thread[t], &status);
         if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
         }
         printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
      }
      
   }
#endif
printf("Main: program completed. Exiting.\n");
pthread_exit(NULL);
}

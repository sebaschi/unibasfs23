#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<pthread.h> 
#define SIZE 10000
#define NUM_THREADS 5
int result;
pthread_mutex_t lock;

struct args
{
	int *arr;
	int start;
	int end;
};

void * accumulate(void * in)
{
	//implement accumlate
	struct args * input = in;
	int * arr = input -> arr;
	int start = input -> start;
	int end = input -> end;
	
	int me = pthread_self();
	int sum = 0;
	
	//sum up the respective part of the array;
	for(int i = start; i <= end; i++){
	//Lock critical section for eatch step. We took the task-description litteraly.
	pthread_mutex_lock(&lock);
	printf("Lock aquired by thread %d\n", me);
	result += arr[i];
	//Unlock critical section.
	pthread_mutex_unlock(&lock);
	printf("Lock released by thread %d, loop: %i\n", me, i);
	}
	
	return NULL;
}
int main ()
{

	result=0;
        int arr[SIZE];    
        for(int i=0;i<SIZE;i++)
		arr[i]=1;

	pthread_t threads[NUM_THREADS-1];
	struct args thread_args[NUM_THREADS-1];
	
	//Loop to populate thread arguments;
	for(int i = 0; i < NUM_THREADS-1; i++ ){
		thread_args[i].arr = arr;
		thread_args[i].start = i * (SIZE/NUM_THREADS);
		thread_args[i].end =  (i+1)*(SIZE/NUM_THREADS)-1;
	}
	//Initialize mutex-lock
	if(pthread_mutex_init(&lock, NULL) != 0){
		printf("\n mutex init has failed :( \n");
		return -1;
	}
	
	//create a team of thread, each thread must take SIZE/NUM_THREADS to accumulate
	//use struct args to pass arguments to the accumulate function
	//Loop to create threads
	for(int i = 0; i < NUM_THREADS-1; i++){
		if(pthread_create(&threads[i], NULL, accumulate, &thread_args[i]) != 0){
			perror("pthread_create failed\n");
			exit(1); 
		}
	}  
	//main thread must participate in the calculation
	//Set start and end for parent thread
	int start = ((NUM_THREADS-1)*SIZE)/NUM_THREADS;
	int end = SIZE;
	//Parent thread goes over its part of the array and only writes to the result when it is free.
	for(int i = start; i < end; i++){
		pthread_mutex_lock(&lock);
		printf("Lock aquired by main thread \n");
		result += arr[i];
		pthread_mutex_unlock(&lock);
		printf("Lock released by main thread \n");
	}
	//make sure all threads finised
	for(int i = 0; i < NUM_THREADS-1; i++){
		if(pthread_join(threads[i], NULL) != 0){
			perror("pthread_join failed");
			exit(1); 
		}
	}
	//Destroy the mutex-lock for fun cleanup
	pthread_mutex_destroy(&lock);
	
	//print the final result.
	printf("sum  is %d\n", result);
}


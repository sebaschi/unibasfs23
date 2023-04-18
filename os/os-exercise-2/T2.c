#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<pthread.h> 
#define SIZE 10000

void swap(int *xp, int *yp);
void sort(int arr[], int size);
float mean(int *arr, int size);
float median(int *arr, int size);



struct thread_data {
    int * arr;
    float * mean;
};

int main (){

        int arr[SIZE];    
        for(int i=SIZE-1;i>=0;i--)
                if(i%2==0)
                        arr[(SIZE-1)-i]=0;
                else
                        arr[(SIZE-1)-i]=1;
        struct thread_data d;
        d->arr = arr;
        d->mean = 0;

        pthread_t mean_t;
        if(pthread_create(&mean_t, NULL, mean, &d) != 0) {
            perror("pthread_create(mean_t) error\n");
            exit(1);
        }



	// TODO implement you solution here
	// TODO a new thread here
        // One thread should calculate the median
        // The other thread should calculate the mean
	// One thread should display the result (mean, median)
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int *arr, int size)
{
   int i, j;
   for (i = 0; i < size-1; i++)    
  
       // Last i elements are already in place   
       for (j = 0; j < size-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

void * mean(int *arr, int size)
{
    int i;
    float res;
    float sum = 0;
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }
    res = sum / size;
    return res;
}

//Return float for even length array since median then mean of two middle values. Assumes Array size>0.
void * median(int *arr, int size)
{
    float res; 
    sort(arr,size);
    if (size % 2 != 0) {
        res = arr[size/2];
    } else {
        res = (arr[size/2-1] + arr[size/2])/2.0;// 2.0 to force floating point division
    }
    return res;
}



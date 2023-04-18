#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<pthread.h> 
#include<sys/mman.h>
#include <fcntl.h>


#define SIZE 10000

void swap(int *xp, int *yp);
void sort(int arr[], int size);
void *  mean(void * args);
float median(int *arr, int size);



struct thread_data {
    int * arr;
    char * mem_name;
};

int main (){

        int arr[SIZE];    
        for(int i=SIZE-1;i>=0;i--)
                if(i%2==0)
                        arr[(SIZE-1)-i]=0;
                else
                        arr[(SIZE-1)-i]=1;
        char * name = "/shmem";
        struct thread_data d = { .arr=arr, .mem_name = name};
        pthread_t mean_t;
        //Start Thread that calculates mean
        int tid = pthread_create(&mean_t, NULL, mean, &d);
        if( tid != 0) {
            perror("pthread_create(mean_t) error\n");
            exit(1);
        }
	//P_thread joins child_thread
        if(pthread_join(mean_t,NULL) != 0){
            printf("Error in mean thread!.\n");
            exit(3);
        }

        float medianres = median(arr, SIZE);
        float meanres;
        int fd = shm_open(name, O_RDWR, 0777);
        float * shres = (float*) mmap(0, sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);
        meanres = *shres;

        

        //Print to  user tty
        printf("Main Thread TID: %ld. Median: %f. Called Thread TID  %ld. Mean: %f\n", pthread_self(), medianres, mean_t, meanres);
        //unmap virtual address
        munmap(shres, sizeof(float));
        //unlink file used for shared memory access
        shm_unlink(name);
        
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

void * mean(void * args)
{
    int i;
    float res;
    float sum = 0;
    struct thread_data * data = args;
    int * arr = data->arr;
    char * mem = data->mem_name;
    for (i = 0; i < SIZE; i++) {
        sum += arr[i];
    }
    res = sum / SIZE;
    float meanres;
    //Open a shared memory object
    int fd = shm_open(mem, O_RDWR | O_CREAT, 0777);
    /*Set size of shared memory object*/
    ftruncate(fd, sizeof(float));
    /*Map into memory*/
    float * shres = (float*) mmap(0,sizeof(float), PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    *shres = res; 
    munmap(shres,sizeof(float));
    close(fd);
    
    return 0;
}

//Return float for even length array since median then mean of two middle values. Assumes Array size>0.
float median(int *arr, int size)
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



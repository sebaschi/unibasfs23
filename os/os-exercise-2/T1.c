#include<stdio.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>

#define SIZE 10000

void swap(int *xp, int *yp);
void sort(int arr[], int size);
float mean(int *arr, int size);
float median(int *arr, int size);


int main ()
{
    int arr[SIZE];         
    for(int i=SIZE-1;i>=0;i--)
        if(i%2==0)
            arr[(SIZE-1)-i]=0;
        else
            arr[(SIZE-1)-i]=1;

    /*Name of shared memory object*/
    const char *name = "/shmem";

    pid_t pid;
    // TODO fork another process here
    pid = fork();
    if (pid <0) {
        printf("Could not fork!\n");
    } else if (pid == 0) {
        //Child Process
        float meanres;
        //Open a shared memory object
        int fd = shm_open(name, O_RDWR | O_CREAT, 0777);
        /*Set size of shared memory object*/
        ftruncate(fd, sizeof(float));
        /*Map into memory*/
        float * shres = (float*) mmap(0,sizeof(float), PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        /*Calculate mean*/
        meanres = mean(arr,SIZE);
        // Debug Statement:
        // printf("Mean in child: %f\n", meanres);
        /*Store mean in shared memory*/
        *shres = meanres;
        munmap(shres,sizeof(float));
        close(fd);
    } else {
        //Wait for child
        int status = 0;
        wait(&status);
        //Get shared mem object 
        int fd = shm_open(name,O_RDWR, 0777);
        //Map into virtual memory
        float * shres = (float*) mmap(0,sizeof(float), PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        //retrieve result of child calculation
        float meanres = *shres;
        //Calculate  median
        float medianres = median(arr, SIZE);
        //Print to  user tty
        printf("Parent pid: %d. Median: %f. Child Pid: %d. Mean: %f\n", getpid(), medianres, pid, meanres);
        //unmap virtual address
        munmap(shres, sizeof(float));
        //unlink file used for shared memory access
        shm_unlink(name);
    }
    // One process should calculate the median
    // The other process should calculate the mean
    // One process should communicate its value to the other process
    // The other process should print both calculated results
    // Hint use shm_open, ftrucate, mmap, and mumap to communicate over mapped files
    return 0;
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

float mean(int *arr, int size)
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
float median(int *arr, int size)
{
    float res; 
    sort(arr,size);
    printf("%d%d\n", arr[size/2], arr[size/2 -1]);
    if (size % 2 != 0) {
        res = arr[size/2];
    } else {
        res = (arr[size/2-1] + arr[size/2])/2.0;// 2.0 to force floating point division
    }
    return res;
}



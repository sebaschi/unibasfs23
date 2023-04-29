/**
 * bounded-buffer problem using the producer-consumer model
 * meant to be solved with counting semaphores and mutex locks
 * 
 * to compile: gcc -o T1 T1.c -lpthread
 * to run: ./T1 <duration> <producer threads> <consumer threads>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define TRUE 1

typedef int buffer_item;
int insertPointer = 0;
int removePointer = 0;

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insert_item(buffer_item item);
int remove_item(buffer_item *item);

void *producer(void *param);
void *consumer(void *param);

int insert_item(buffer_item item)
{
     // Aquire empty semaphore and decrement.
    if (sem_wait(&empty) != 0) {
        printf("Error decrementing empty semaphore.\n");
        return -1;
    }
    // Aquire mutex lock.       
    if (pthread_mutex_lock(&mutex) != 0) {
        printf("Error locking mutex\n");
        return -1;
    }
        
    //Enter critical section.   
    buffer[insertPointer++] = item;
    insertPointer = insertPointer % BUFFER_SIZE;

    // Release mutex lock and increment full semaphore.
    if (pthread_mutex_unlock(&mutex) != 0) {
        printf("Error unlocking mutex\n");
        return -1;
    }
    if (sem_post(&full) != 0) {
        printf("Error incrementing full semaphore\n");
        return -1;
    }
    return 0;
}

int remove_item(buffer_item *item)
{

    // Decrement full semaphore.
    if (sem_wait(&full) != 0) {
        printf("Error decrementing full semaphore\n");
        return -1;
    }
    // Aquire mutex lock.
    if (pthread_mutex_lock(&mutex) != 0) {
        printf("Error locking mutex\n");
        return -1;
    }

    *item = buffer[removePointer];
    buffer[removePointer++] = -1;
    removePointer = removePointer % BUFFER_SIZE;


    // Unlock mutex
    if (pthread_mutex_unlock(&mutex) != 0) {
        printf("Error unlocking mutex\n");
        return -1;
    }

    // Increment empty semaphore.
    if (sem_post(&empty) != 0) {
        printf("Error incrementing empty semaphore\n");
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int duration, producerThreads, consumerThreads;
    int i, j;

    if (argc != 4)
    {
        fprintf(stderr, "Useage: <duration> <producer threads> <consumer threads>\n");
        return -1;
    }

    duration = atoi(argv[1]);
    producerThreads = atoi(argv[2]);
    consumerThreads = atoi(argv[3]);

    // TODO initialize the synchronization tools
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Error initializing mutex\n");
        return -1;
    }
    if (sem_init(&empty, 0, BUFFER_SIZE) != 0) {
        printf("Error initializing empty semaphore\n");
        return -1;
    }
    if (sem_init(&full, 0, 0) != 0) {
        printf("Error initializing full semaphore\n");
        return -1;
    }

    srand(time(0));

    // create the producer and consumer threads
    for (i = 0; i < producerThreads; i++)
    {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, producer, NULL);
    }

    for (j = 0; j < consumerThreads; j++)
    {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, consumer, NULL);
    }

    // sleep for user specified time
    sleep(duration);
    return 0;
}

void *producer(void *param)
{
    buffer_item random;
    int r;

    while (TRUE)
    {
        r = rand() % 5;
        sleep(r);
        random = rand();

        if (insert_item(random))
            fprintf(stderr, "Error");

        printf("Producer produced: %d, buffer position: %d \n", random, (insertPointer + 4) % 5);
    }
}

void *consumer(void *param)
{
    buffer_item random;
    int r;

    while (TRUE)
    {
        r = rand() % 5;
        sleep(r);

        if (remove_item(&random))
            fprintf(stderr, "Error Consuming");
        else
            printf("Consumer consumed: %d, buffer position: %d \n", random, (removePointer + 4) % 5);
    }
}

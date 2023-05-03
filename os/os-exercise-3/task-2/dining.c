#include "dp.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int left_neighbor(int number)
{
    if (number == 0)
        return NUMBER - 1;
    else
        return number - 1;
}

int right_neighbor(int number)
{
    if (number == NUMBER - 1)
        return 0;
    else
        return number + 1;
}

void test(int i)
{
    // if philosopher is hungry, and left and right neighbor are not eating, then eat
    if ((state[i] == HUNGRY) && (state[left_neighbor(i)] != EATING) && (state[right_neighbor(i)] != EATING))
    {
        state[i] = EATING;

        // TODO unblock threads from condition variable
        pthread_cond_signal(&cond_vars[i]);
    }
}

void pickup_forks(int number)
{
    pthread_mutex_lock(&mutex_lock);

    state[number] = HUNGRY;
    test(number);

    while (state[number] != EATING)
    {
        sleep(1);

        // TODO wait on condition variable and mutex
        pthread_cond_wait(&cond_vars[number], &mutex_lock);
        printf("Philosopher %d completed waiting\n", number);
    }

    pthread_mutex_unlock(&mutex_lock);
}

void return_forks(int number)
{
    pthread_mutex_lock(&mutex_lock);
    printf("Philosopher %d is returning forks\n", number);
    state[number] = THINKING;
    test(left_neighbor(number));
    test(right_neighbor(number));

    pthread_mutex_unlock(&mutex_lock);
}

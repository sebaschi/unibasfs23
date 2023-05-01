#include "dp.h"
#include "dining.c"
#include <pthread.h>
#include <stdio.h>
#include <time.h>

// structure of a dining philosopher alternating between thinking and eating
void *philosopher(void *param)
{
    int *lnumber = (int *)param;
    int number = *lnumber;
    int sleep_time;
    int times_through_loop = 0;

    srandom((unsigned)time(NULL));

    while (times_through_loop < 2)
    {
        printf("Philosopher %d is thinking\n", number);
        sleep((int)((random() % MAX_SLEEP_TIME) + 1));

        pickup_forks(number);

        printf("Philosopher %d is eating\n", number);
        sleep((int)((random() % MAX_SLEEP_TIME) + 1));

        return_forks(number);

        ++times_through_loop;
    }

    printf("Philosopher %d is done\n", number);
}

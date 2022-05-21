#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sched.h>
#include<stdbool.h>
#include<assert.h>

int get_cpu_affinity() {

    cpu_set_t mask;
    long nproc, i;

    nproc = sysconf(_SC_NPROCESSORS_ONLN);
    return CPU_ISSET(i, &mask);
}

void whatScheduler(int i)
{

    switch (i)
    {
        case 0: printf("Normal");
            break;
        case 1: printf("FIFO");
            break;
        case 2: printf("RoundRobin");
            break;
        case 3: printf("BATCH");
            break;
        case 4: printf("IDLE");
            break;
        default: printf("Error getting Scheduling Algorithm");
            break;
    }
}

void *xFunction()
{
    cpu_set_t mask;
    printf("BlackHole Thread X: PID-%d CPU-%d Affinity-%d Algorithm-",getpid(), sched_getcpu(), get_cpu_affinity());
    whatScheduler(sched_getscheduler(getpid()));
    printf("\n");
    pthread_exit(NULL);
}

void *yFunction()
{
    cpu_set_t mask;
    printf("BlackHole Thread Y: PID-%d CPU-%d Affinity-%d Algorithm-",getpid(), sched_getcpu(), get_cpu_affinity());
    whatScheduler(sched_getscheduler(getpid()));
    printf("\n");
    pthread_exit(NULL);
    
}

int main()
{
    pthread_t x, y;
    for(int i = 0; i < 100; i++)
    {
        pthread_create(&x, NULL, xFunction, NULL);
        pthread_create(&y, NULL, yFunction, NULL);
        pthread_join(x, NULL);
        pthread_join(y, NULL);
    }

    exit(1);
}

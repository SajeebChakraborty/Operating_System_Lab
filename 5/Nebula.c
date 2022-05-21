#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sched.h>
#include<stdbool.h>
#include<assert.h>



void Scheduler_check(int pid)
{

    if(pid==0)
    {
    
    	 printf("default algorithm");
    
    }
    else if(pid==1)
    {
    
    	printf("FIFO algorithm");
    
    }
    else if(pid==2)
    {
    
    	printf("RoundRobin algorithm");
    
    }
    else if(pid==3)
    {
    
    	printf("Batch algorithm");
    
    }
    else if(pid==4)
    {
    
    	printf("IDle algorithm");
    
    }

}

int print_affinity() {
    cpu_set_t mask;
    long nproc, i;

    if (sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_getaffinity");
        assert(0);
    }
    nproc = sysconf(_SC_NPROCESSORS_ONLN);
    return CPU_ISSET(i, &mask);
}

void *xFunction()
{
    cpu_set_t mask;
    printf("Nebula Thread X: PID-%d CPU-%d Affinity-%d Algorithm-",getpid(), sched_getcpu(), print_affinity());
    Scheduler_check(sched_getscheduler(getpid()));
    printf("\n");
    pthread_exit(NULL);
}

void *yFunction()
{
    cpu_set_t mask;
    printf("Nebula Thread Y: PID-%d CPU-%d Affinity-%d Algorithm-",getpid(), sched_getcpu(), print_affinity());
    Scheduler_check(sched_getscheduler(getpid()));
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

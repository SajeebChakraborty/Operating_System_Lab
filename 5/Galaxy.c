#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sched.h>
#include<stdbool.h>
#include<assert.h>
#include<sys/wait.h>

int get_cpu_affinity() {
    cpu_set_t mask;
    long nproc, i;

    nproc = sysconf(_SC_NPROCESSORS_ONLN);
    return CPU_ISSET(i, &mask);
}

void Scheduler_check(int i)
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

int main()
{
    int i, child = 2;
    pid_t cpid;
    
    printf("Galaxy: PID-%d CPU-%d Affinity-%d Algorithm-",getpid(), sched_getcpu(), get_cpu_affinity());
    Scheduler_check(sched_getscheduler(getpid()));
    printf("\n");

    for(i = 0; i < child; i++)
    {
        cpid = fork();

        if(cpid == 0)
        {
            break;
        }
    }

    if(cpid == 0)
    {
        if(i == 0)
        {
            execlp("./Nebula", "./Nebula", (char *) NULL);
        }
    }

    if(cpid == 0)
    {
        if(i == 1)
        {
            execlp("./BlackHole", "./BlackHole", (char *) NULL);
        }
    }

    if(cpid > 0)
    {
        int status;
        pid_t pid;
        while ((pid = wait(&status)) > 0);

    }
    return 0;
}

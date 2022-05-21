#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sched.h>
#include<sys/wait.h>


int sched_getcpu(void);


int main()
{

	
	while(1)
	{
	
		printf("Killow pid %d cpu %d\n",getpid(),sched_getcpu());
	
	}


}

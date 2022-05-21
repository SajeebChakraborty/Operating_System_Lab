#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sched.h>
#include<sys/wait.h>


int sched_getcpu(void);


int main()
{

	
	pid_t killow,pillow;
	
	
	
	
	killow=fork();
	
	if(killow<0)
	{
	
		exit(-1);
		printf("Not child created !\n");
		
	
	}
	else if(killow>0)
	{
	
		
		
	
		pillow=fork();
		
		if(pillow<0)
		{
		
			exit(-1);
			printf("child is not created !\n");
		
		}
		else if(pillow==0)
		{
		
			execlp("/home/Desktop/lt/1/Pillow","Pillow",NULL);
			//execlp("Pillow","Pillow",NULL);
		
		}
		else
		{
			while(1)
			{
		
				printf("Mellow pid %d and cpu %d\n",getpid(),sched_getcpu());
		
			}	
		
		
		}
		wait(NULL);
		
		
	}
	else
	{
	
		execlp("/home/Desktop/lt/1/Killow","Killow",NULL);
		//execlp("Killow","Killow",NULL);
	
	}
	





}

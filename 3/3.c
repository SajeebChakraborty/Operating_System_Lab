#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h> 
#include <stdlib.h>
#include<sched.h>
#include<signal.h>
#include<sys/syscall.h>
#include<unistd.h>
int result=0;





pthread_mutex_t key;

void Ittu(void *arr)
{

	pthread_mutex_lock(&key);
	
		int *y=arr;

		result=result + y[0]+y[1];
		
	
	
		printf("Ittu sum result = %d pid %d tid %d cpu %d\n",result,getpid(),gettid(),sched_getcpu());
		
		if(result==100)
		{
		
			kill(getpid(),SIGKILL);
		
		
		}	
	
	pthread_mutex_unlock(&key);




}
void Bittu(void *arr)
{

	pthread_mutex_lock(&key);

		int *y=arr;
		
		result=result + y[0]-y[1];
		
		
	
		printf("Bttu sub result = %d pid %d tid %d cpu %d\n",result,getpid(),gettid(),sched_getcpu());
		
		
		if(result==100)
		{
		
			kill(getpid(),SIGKILL);
		
		
		}

	
	
	pthread_mutex_unlock(&key);



}

void Mittu(void *arr)
{

	pthread_mutex_lock(&key);

		int *y=arr;
		
		result=result + y[0]*y[1];
		
			
	
		printf("Mittu mul result = %d pid %d tid %d cpu %d\n",result,getpid(),gettid(),sched_getcpu());
		
		if(result==100)
		{
		
			kill(getpid(),SIGKILL);
		
		
		}
	
	
	
	pthread_mutex_unlock(&key);



}


int main()
{

	for(int i=1;i<=100;i++)
	{
		int arr[2];
		
		
		
		printf("Enter the 2 value : ");
		scanf("%d %d",&arr[0],&arr[1]);
		
		

		pthread_t tid1,tid2,tid3;
		
		pthread_create(&tid1,NULL,(void *) Ittu,(void *)arr);
		pthread_create(&tid2,NULL,(void *) Bittu,(void *)arr);
		pthread_create(&tid3,NULL,(void *) Mittu,(void *)arr);
		
		
		if(result==100)
		{
		
			exit(-1);	
			
		}
		
		
		pthread_join(tid1,NULL);
		pthread_join(tid2,NULL);
		pthread_join(tid3,NULL);
	
	}



}

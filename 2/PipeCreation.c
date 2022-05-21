#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int args, char *arg[])
{
	
	
	
	
	
	for(int i=1;i<args;i++)
	{
	
		if(access(arg[i],F_OK)==0)
		{
		
			printf("Pipe already created !\n");
		
		}
		else
		{
			//printf("%s\n",arg[i]);
			mkfifo(arg[i], 0666);
		
			printf("Pipe has been created successfully.\n");
		
		}
	
		
	
	}
	



}

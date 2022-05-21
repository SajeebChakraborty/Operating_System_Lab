#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(int args, char *arg[])
{

	char buffer[200];
	int cnt=1;
	

	while(1)
	{
	
		
		
		char *path;

		int id,fd;
		path=arg[1];
		fd=open(path,O_RDONLY);
			
		read(fd,buffer,sizeof(buffer));
		close(fd);
		printf("%s\n",buffer);
		if(strcmp(buffer,"Bye")==0)
		{
		
			
			char *buffer2="Bye";
			fd=open(path,O_WRONLY);
			
			write(fd,buffer2,strlen(buffer2)+1);
			break;
			
			
			
		
		
			
		
		}
		

	
	}
	


}

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int args, char *arg[])
{
	int id,fd;
	char str[105];
	id=getpid();
	sprintf(str,"Hello pid=%d parent id=%d",id,getppid());
	fd=open(arg[1],O_WRONLY);
	write(fd,str,strlen(str)+1);
	char *path;
	
	while(1)
	{
		
		
		
		path=arg[1];
		scanf("%s",str);
		
		
		
		
		
		write(fd,str,strlen(str)+1);
		//read(fd,str,strlen(str)+1);
		//printf("%s",str);
		
		if(strcmp(str,"Bye")==0)
		{
		
			break;
		
		}
		
		
	}
	close(fd);
	char buffer[105];
	fd=open(path,O_RDONLY);
			
	read(fd,buffer,sizeof(buffer));
	printf("%s\n",buffer);
	close(fd);

}

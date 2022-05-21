#define _GNU_SOURCE
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/prctl.h>  


int create_shared_memory(){
key_t key;
int shmID;

key = ftok("process_semaphore.c", 'a');
shmID = shmget(key, 1024, IPC_CREAT | 0666);

return shmID;
}

void write_to_shm(int x){
int shmID = create_shared_memory();


char *str = shmat(shmID, NULL, 0);


char num[100];
sprintf(num, "%d", x);

strcpy(str, num);


shmdt(str);
}

int read_from_shm(){
int shmID = create_shared_memory();


char *str = shmat(shmID, NULL, 0);


int num = (int) strtol(str, (char **)NULL, 10);


shmdt(str);

return num;
}

int main(){
	sem_t * sem;
	pid_t childPID;
	int a, b, result, shmid, i, check;

    	scanf("%d%d", &a, &b);


	result = 0; 
	write_to_shm(result);


	shmid = shmget(0,sizeof(sem) + SHMLBA, IPC_CREAT | 0666);


    	sem = shmat(shmid, NULL, 0);


    	sem_init(sem, 1, 1);

	for (i = 0; i < 3; i++) {

		childPID = fork();

		if (childPID < 0) {
		printf("Process creation failed\n");
		exit(-1);
		} 
		else if (childPID == 0){ 
			if (i == 0) 
			{
				prctl(PR_SET_NAME, "Ittu");
				sem_wait(sem);
			       
				int x = read_from_shm();
		printf("result: %d in Child-%d [Core: %d] Before Addition\n", x, getpid(), sched_getcpu());
				printf("a = %d, b = %d\n", a, b);

				int temp = a + b;
		write_to_shm(x + temp);

				int y = read_from_shm();
		printf("result: %d in Child-%d [Core: %d] After Addition\n", y, getpid(), sched_getcpu());

				sem_post(sem);
				exit(0);
			}
			else if (i == 1) 
			{
				prctl(PR_SET_NAME, "Bittu");
		sem_wait(sem);

		int x = read_from_shm();
		printf("result: %d in Child-%d [Core: %d] Before Subtraction\n", x, getpid(), sched_getcpu());
				printf("a = %d, b = %d\n", a, b);

				int temp = a - b;
		write_to_shm(x + temp);

				int y = read_from_shm();
		printf("result: %d in Child-%d [Core: %d] After Subtraction\n", y, getpid(), sched_getcpu());

				sem_post(sem);
				exit(0);
			}	
			else if (i == 2) 
			{
				prctl(PR_SET_NAME, "Mittu");
				sem_wait(sem);

				int x = read_from_shm();
		printf("result: %d in Child-%d [Core: %d] Before Multiplication\n", x, getpid(), sched_getcpu());
				printf("a = %d, b = %d\n", a, b);

				int temp = a * b;
				write_to_shm(x + temp);

				int y = read_from_shm();
		printf("result: %d in Child-%d [Core: %d] After Multiplication\n", y, getpid(), sched_getcpu());

				sem_post(sem);
				exit(0);
			    }

			}
			else
			{ 
				waitpid(childPID, NULL, 0);

				sem_wait(sem);

			int x = read_from_shm();
			printf("result: %d in Parent [Core: %d]\n", x, sched_getcpu());

			sem_post(sem);
			}
	}

	return 0;
}

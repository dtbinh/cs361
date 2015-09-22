
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t pid, pid1;
	
	int number = 15;
	pid = fork();
	
	switch( pid )
	{
		case -1:
			printf("Fork Failed\n");
			return 1;
		case 0:
			pid1 = getpid();
			printf("Inside Child: pid = %d\n", pid);
			printf("Inside Child: pid1 = %d\n", pid1);
			number += 5;
			printf("Inside Child: number = %d\n", number);
			break;
		default:
			printf("Inside Parent:I will wait till child exits\n");
			wait(NULL);
			number += 100;
			pid1 = getpid();
			printf("Inside Parent: pid = %d\n", pid);
			printf("Inside Parent: pid1 = %d\n", pid1);
			printf("Inside Parent: number = %d\n", number);
	}
	return 0;
}


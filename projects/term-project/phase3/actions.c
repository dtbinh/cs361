/*
 * actions.c
 *
 * Modified on: Oct 26, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef ACTIONS_C_
#define ACTIONS_C_

#include <stdio.h>
#include "actions.h"
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/stat.h>

int attempts = 0;
int order_size = 0;

void getAddress()
{
	printf("Got the address.\n");
}

void chargeClient()
{
	printf("Charged the client.\n");
}

void startWarranty()
{
	printf("Started the warranty.\n");
}

void updateStats(stats value)
{
	if(value == 0)
	{
		printf("Stats updated to: DONE!\n");
	}
	else if(value == 1)
	{
		printf("Stats updated to: LOST!\n");
	}
	else if(value == 2)
	{
		printf("Stats updated to: FAIL!\n");
	}
	else
	{
		printf("ERROR IN UPDATE!!!\n");
	}

}

void refund()
{
	printf("Refunded due to lost package.\n");
}

void resetAttempts()
{
	attempts = 0;
	printf("Attempts have been reset.\n");
}

int incrementAttempts()
{
	attempts += 1;
	printf("Attempts have been incremented.\n");
	if(attempts == 3)
	{
		printf("You have reached the maximum number of attempts.\n");
	}
	else
	{
		int calc;
		calc = (3-attempts);
		printf("The maximum number of payment attempts is 3. "
					 "You only have %d attempts left!\n", calc);
	}

	return attempts;
}

void getPaymentMethod()
{
	printf("Payment method has been acquired.\n");
}

void dispatchFactoryLines()
{
	int shmid,
			shmflg;
	key_t shmkey;
	shared_data *p;

	int ii, capacity, duration;
	pthread_t tid1, tid2, tid3, tid4, tid5;
	pid_t pid;
	char userprog[50];

	shmkey = SHMEM_KEY ;
	shmflg = IPC_CREAT | S_IRUSR | S_IWUSR  /* | IPC_EXCL */ ;

	shmid = shmget( shmkey , SHMEM_SIZE , shmflg );

	if (shmid == -1)
	{
		printf("\nFailed to create/find shared memory '0x%X'.\n", shmkey );
		perror("Reason:");
		exit(-1);
	}

	p = (shared_data *) shmat( shmid , NULL , 0 );
	if (p == (shared_data *) -1)
	{
		printf ("\nFailed to attach shared memory id=%d\n" , shmid );
		perror("Reason:");
		exit(-1) ;
	} 

	printf("Factory lines dispatched.\n");

	p->parts_remaining = 0;
	p->total = 0;
	p->lines_active = 5;

	//sets the random seed value and assigns a random value to
	//order_size between 1000-2000 (inclusively)
	srandom(time(NULL));
	order_size = (random() % 1001) + 1000;
	printf("Order Size: %d\n", order_size);

	//sets parts_remaining, which will be used to keep track of how long the
	//threads will run
	p->parts_remaining = order_size;
	sem_init(&(p->cntMutex), 1, 1);
	sem_init(&(p->factory_lines_finished), 1, 0);

	//for(int ii = 0; ii < 5; ii++)
	//creates the 5 threads
  /* execlp child processes */

	// Create supervisor process
	pid = fork();
	switch (pid)
	{
		case -1:
			perror("Fork failed");
			exit(-1);

		case 0:
			if ( execlp("gnome-terminal", "superVterm", "-x", "/bin/bash",
									"-c", "./supervisor 5", NULL) == -1 )
			{
				perror("Failed to exec supervisor process");
				exit(-1);
			}

		default:
			break;
	}
	
	// Create 5 factory line processes
	for (ii = 1; ii <= 5; ii++)
	{
		capacity = (random() % 41) + 10;  //sets random capacity between 10-50
		duration = (random() % 5) + 1;  //sets random duration between 1-5
		pid = fork();
		switch (pid)
		{
			case -1:
				perror("Fork failed");
				exit(-1);

			case 0:
				sprintf(userprog, "./factoryline %d %d %d", ii, capacity, duration);
				if ( execlp("gnome-terminal", "SuperVterm", "-x", "/bin/bash", "-c",
										userprog, NULL) == -1 )
				{
					perror("Failed to exec factoryline process");
					exit(-1);
				}

			default:
				break;
		}
	}

	sem_wait(&(p->factory_lines_finished));
	printf("\nTotal Items Produced: %d\n", p->total);

}

void shutDownFactoryLines()
{
	printf("Factory lines shutdown.\n");
}

#endif

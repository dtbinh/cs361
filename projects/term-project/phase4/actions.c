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
	int ii;
	pid_t pid;

	printf("Factory lines dispatched.\n");

	/* Create supervisor process */
	pid = fork();
	switch (pid)
	{
		case -1:
			perror("Fork failed");
			exit(-1);

		case 0:
			if ( execlp("gnome-terminal", "superVterm", "-x", "/bin/bash",
									"-c", "./server 66", NULL) == -1 )
			{
				perror("Failed to exec supervisor process");
				exit(-1);
			}

		default:
			break;
	}
}

void shutDownFactoryLines()
{
	printf("Factory lines shutdown.\n");
}

#endif

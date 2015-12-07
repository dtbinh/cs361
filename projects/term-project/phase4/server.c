/*
 * server.c
 *
 * Modified on: Dec 6, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "mySock.h"
#include "actions.h"
#include "message.h"

int main(int argc, char** argv)
{
	int curLines = 5;
	int iters[5], prod[5], cap[5], dur[5];

	msgBuffer msg;

	for (int ii = 0; ii < 5; ii++)
	{
		iters[ii] = 0;
		prod[ii] = 0;
		cap[ii] = 0;
		dur[ii] = 0;
	}

	printf("Server is Waiting on Client...\n");

	while(curLines > 0) {
			if (msg.data.quit == 1)
			{
				iters[msg.data.id - 1]++;
				cap[msg.data.id - 1] = msg.data.cap;
				dur[msg.data.id - 1] = msg.data.dur;
				prod[msg.data.id - 1] += msg.data.prod;
			}
			else if (msg.data.quit == 2)
			{
				curLines--;
			}
			else
			{
				printf("ERROR!\n");
			}
	}

	for (int ii = 0; ii < 5; ii++)
	{
		printf("\nFactory Line: %d\n", ii+1);
		printf("\tProduction: %d\n", prod[ii]);
		printf("\tCapacity: %d\n", cap[ii]);
		printf("\tIterations: %d\n", iters[ii]);
		printf("\tDuration: %d\n", dur[ii]);
	}

	printf("\nSERVER GOING OFFLINE\n");
	return 0;
}

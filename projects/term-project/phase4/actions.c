/*
 * actions.c
 *
 * Modified on: Dec 6, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef ACTIONS_C_
#define ACTIONS_C_

#include <stdio.h>
#include "mySock.h"
#include "actions.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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

//handles the factory line productions (AKA the clients)
void dispatch_factory_lines()
{
	int iters[5], dur[5], numOrder[5];
	struct sockaddr_in  fsn;   //address of client
    unsigned short portNum = 26 ;  //port num
	int orderSize, id, socket, finished, curLines;
    unsigned int aa;  //address len
    int totalLines;

    actionsMsg aMsg;
    serverMsg sMsg;

	printf ("Factory lines dispatched.\n\n");
	socket = serverUDPsock(portNum);

	for (int ii = 0; ii < 5; ii++) {
		iters[ii] = 0;
		dur[ii] = 0;
		numOrder[ii] = 0;
	}

	srand (time(NULL));
	orderSize = (order_H + rand() / (RAND_MAX/(order_L - order_H + 1) + 1));
	printf("\nSize of Order: %d\n\n", orderSize);
	id = 0;
	finished = 0;

	totalLines = 0;
	curLines = 0;
	while(finished != 1)
    {
		aa = sizeof(fsn);
        if(recvfrom(socket, (void *) &aMsg, sizeof(aMsg), 0, (SA *) &fsn, &aa) < 0)
        {
            err_sys("Error");
        }

		if(aMsg.mestype == 1)
		{
			curLines++;
			totalLines++;

			sMsg.data.dur = (dur_H + rand() / (RAND_MAX / (dur_L - dur_H + 1) + 1));
			sMsg.data.cap = (cap_H + rand() / (RAND_MAX / (cap_L - cap_H + 1) + 1));

			sMsg.mestype = 1;
			sMsg.data.id = ++id;

		}
		else if(aMsg.mestype == 2)
		{
			if(orderSize == 0)
			{
				sMsg.mestype = 3;
			}
			else if(orderSize >= aMsg.data.cap)
			{
				sMsg.data.items = aMsg.data.cap;
				orderSize = aMsg.data.cap - 1;
				sMsg.mestype = 2;
			}
			else {
				sMsg.data.items = orderSize;
				orderSize = 0;
				sMsg.mestype = 2;
			}
		}
		else
		{
			curLines--;
			dur[aMsg.data.id - 1] = aMsg.data.dur;
			numOrder[aMsg.data.id - 1] = aMsg.data.items;


			iters[aMsg.data.id - 1] = aMsg.data.iters;
			if (curLines < 1) {
				finished = 1;

				//printing out the Factory Line information
				for (int ii = 0; ii < totalLines; ii++){
					printf("\nLine %d\n", ii+1);
					printf("Produced: %d\n", numOrder[ii]);
					printf("Iterations: %d\n", iters[ii]);
					printf("Duration: %dms\n", dur[ii]);

				}
			}
		}

		if (finished != 1)
		{
			sendto(socket, (void *) &sMsg, sizeof(sMsg), 0, (SA *) &fsn, aa);
		}
	}

	printf("\nFactory Lines Production Complete.\n");
}

//shuts down the factory lines
void
shut_down_factory_lines()
{
	printf ("Factory Lines Shut Down.\n");
}

#endif

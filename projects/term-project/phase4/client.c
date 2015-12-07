/*
 * client.c
 *
 * Modified on: Dec 6, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


#include "mySock.h"
#define MAXBUFLEN 256

int main(int argc, char** argv)
{
	struct timespec time1, time2;

	char *host = argv[1];
	char *port = argv[2];
	int id, dur, totalDur, cap, iters, prod, finished, sd, rc;

	finished = 0;
	totalDur=0;
	iters=0;

    actionsMsg aMsg;
    serverMsg  sMsg;
    aMsg.mestype = 1;

    sd = clientUDPsock(host, port);
	while (finished != 1) {
		sendto(sd, (void *) &aMsg, sizeof(aMsg) , NULL , 0 );
		rc = recvfrom(sd, (void*) &sMsg , sizeof(sMsg) , NULL , 0 );

		//no instructions passed to client
		if (rc <= 0)
		{
		    err_sys("Error - No instructions recieved!");
		}

		//Prints out factory line's duration and capacity
		if (sMsg.mestype == 1)
		{
			printf("Line: %d - Duration: %d - Capacity: %d.\n", sMsg.info.id, sMsg.info.dur, sMsg.info.cap);

			id = sMsg.info.id;
			cap = sMsg.info.cap;
			dur = sMsg.info.dur;
			aMsg.info.cap = cap;
			prod = 0;
			time1.tv_sec = 0;
			time1.tv_nsec = (dur * 1000000);
			aMsg.mestype = 2;
		}
		//Client doing it's work
		else if (sMsg.mestype == 2)
		{
			aMsg.info.cap = cap;
			aMsg.info.id = id;

			nanosleep(&time1, &time2); //sleeping to simulate product working

			iters++;
			prod += sMsg.info.items;
			totalDur += dur;
			aMsg.mestype = 2;
		}
		//COMPLETE
		else
		{
			printf("Line %d: %d Iterations, %dms Total Duration, Produced %d Items\n", id, iters, totalDur, prod);
			printf("Line %d's order is complete!\n", id);
			aMsg.mestype = 3;
			aMsg.info.dur = totalDur;
			aMsg.info.items = prod;
			aMsg.info.iters = iters;
			finished = 1;
		}
	}

	//exiting the client
	sendto(sd, (void *) &aMsg, sizeof(aMsg) , NULL , 0 );
    exit(0);
}

/*
 * message.h
 *
 * Modified on: Dec 6, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */
#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <sys/types.h>

#define MAXNAMELEN 20

typedef struct
{
	long mestype;
	struct
	{
		int id;
		int quit;
		int cap;
		int prod;
		int dur;
	} data;
} msgBuffer;

#define MSG_INFO_SIZE ( sizeof(msgBuf) - sizeof(long))
#define BASE_MAILBOX_NAME 0x32

void printMsg( msgBuffer *m);

#endif

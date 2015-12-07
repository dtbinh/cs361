/*
 * message.h
 *
 * Modified on: Dec 6, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */
#ifndef MESSAGE_H_
#define MESSAGE_H_
 
#include <sys/types.h>
#include <semaphore.h>

#define MAXNAMELEN 20

typedef struct {
	long mestype;
	struct {
		int id, quit, cap, prod, dur;
	} data;
} msgBuffer;

#define MSG_INFO_SIZE ( sizeof(msgBuf) - sizeof(long))
#define BASE_MAILBOX_NAME 0x32

void printMsg( msgBuf *m);

#endif

/*
 * mySock.h
 *
 * Modified on: Dec 6, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

void err_quit(const char* x);
void err_sys(const char* x);
int clientUDPsock(const char *host, const char *service ) ;
int serverUDPsock(const unsigned short port) ;

typedef struct 
{
	long mestype;
	struct 
	{
		int id;
		int cap; 
		int items;
		int dur;
		int iters;
	} info;
} actionsMsg;

typedef struct 
{
	long mestype;
	struct 
	{
		int id;
		int cap;
		int items;
		int dur;
	} info;
} serverMsg;

typedef struct sockaddr SA ;
#define BASEPORT 50000

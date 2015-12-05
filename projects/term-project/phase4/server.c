#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "mySock.h"
#define MAXBUFLEN   256

/*------------------------------------------------------------------------
 * main - Iterative UDP server for DAYTIME service
 *------------------------------------------------------------------------
 */

int main(int argc, char *argv[])
{
  struct sockaddr_in  fsin;   /* the from address of a client */
  unsigned short port = 13 ;  /* service name or port number  */
  char    buf[MAXBUFLEN];     /* "input" buffer; any size > 0 */
  int	    sock;               /* server socket                */
  time_t	now;                /* current time                 */
  char    timeStr[MAXBUFLEN]; /* time string   */
  unsigned int    alen;       /* from-address length          */
	int ii, capacity, duration, lines_active;
  
  switch (argc) 
    {
    case 1:
      break;
    case 2:
      port = atoi( argv[1] );
      break;
    default:
      snprintf(buf, MAXBUFLEN , "usage: %s [port]\n" , argv[0] );
      err_quit( buf ) ;
    }
  
	srandom(time(NULL));
  sock = serverUDPsock(port);
  lines_active = 0;
	order_size = (random() % 1001) + 1000;
  capacity = (random() % 41) + 10;  //sets random capacity between 10-50
  duration = (random() % 5) + 1;  //sets random duration between 1-5
  
  while (1) 
    {
      alen = sizeof(fsin);
      //`fprintf(stderr , "DAYTIME server waiting\n" ) ;        

      if ( recvfrom( sock, buf, MAXBUFLEN , 0, (SA *) &fsin, &alen ) < 0 )
        err_sys( "recvfrom" ) ;

      fprintf(stderr , "DAYTIME server received '%s'\n" , buf ) ;
      if (strcmp(buf, "start") == 0)    /* Factory line is ready to begin */
        {
          sendto( sock , (char *) &timeStr , strlen(timeStr) , 0 ,
                 (SA *) &fsin, alen );
        }
      
      time( &now ); /* get the current system's time */
      ctime_r( &now , timeStr );    /* WARNING! ctime() is NOT thread-safe */
      fprintf(stderr , "DAYTIME server sending '%s'\n" , timeStr ) ;
      sendto( sock , (char *) &timeStr , strlen(timeStr) , 0 , 
             (SA *) &fsin, alen );
    }
}
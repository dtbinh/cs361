#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "message.h"
#include "mySock.h"
#define MAXBUFLEN   256

int main(int argc, char *argv[])
{
  struct sockaddr_in  fsin;   /* the from address of a client */
  struct sockaddr_in  fsin1;   /* the from address of a client */
  struct sockaddr_in  fsin2;   /* the from address of a client */
  struct sockaddr_in  fsin3;   /* the from address of a client */
  struct sockaddr_in  fsin4;   /* the from address of a client */
  struct sockaddr_in  fsin5;   /* the from address of a client */
  unsigned short port = 13 ;  /* service name or port number  */
  char    buf[MAXBUFLEN];     /* "input" buffer; any size > 0 */
  msgBuf from_msg;            /* message received             */
  msgBuf to_msg;              /* message sent                 */
  int	    sock;               /* server socket                */
  time_t	now;                /* current time                 */
  char    timeStr[MAXBUFLEN]; /* time string                  */
  unsigned int    alen;       /* from-address length          */
	int ii, order_size, parts_remaining,
      duration, lines_active, total_produced, done;
  
  switch (argc) 
    {
    case 1:
      break;
    case 2:
      port = atoi( argv[1] );
      printf("PORT %d\n", port);
      break;
    default:
      snprintf(buf, MAXBUFLEN , "usage: %s [port]\n" , argv[0] );
      err_quit( buf ) ;
    }
  
	srandom(time(NULL));
  sock = serverUDPsock(port);
  lines_active = 0;
  total_produced = 0;
	order_size = (random() % 1001) + 1000;
	parts_remaining = order_size;

  done = 0;

  printf("Order size: %d\n", order_size);
  
  /* NEW LINE */
  if ( recvfrom( sock, (void *)&from_msg, sizeof(from_msg), 0, (SA *) &fsin, &alen ) < 0 )
    err_sys( "recvfrom" );
  fsin1 = fsin;

  lines_active++;
  to_msg.info.factory_ID = lines_active;
  to_msg.info.capacity = (random() % 41) + 10;
  to_msg.info.duration = /*(random() % 5) + 1*/ 1;
  to_msg.info.produce = to_msg.info.capacity;

  sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin1, alen );
  
  /* NEW LINE */
  if ( recvfrom( sock, (void *)&from_msg, sizeof(from_msg), 0, (SA *) &fsin, &alen ) < 0 )
    err_sys( "recvfrom" );
  fsin2 = fsin;

  lines_active++;
  to_msg.info.factory_ID = lines_active;
  to_msg.info.capacity = (random() % 41) + 10;
  to_msg.info.duration = /*(random() % 5) + 1*/ 1;
  to_msg.info.produce = to_msg.info.capacity;

  sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin2, alen );
  
  /* NEW LINE */
  if ( recvfrom( sock, (void *)&from_msg, sizeof(from_msg), 0, (SA *) &fsin, &alen ) < 0 )
    err_sys( "recvfrom" );
  fsin3 = fsin;

  lines_active++;
  to_msg.info.factory_ID = lines_active;
  to_msg.info.capacity = (random() % 41) + 10;
  to_msg.info.duration = /*(random() % 5) + 1*/ 1;
  to_msg.info.produce = to_msg.info.capacity;

  sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin3, alen );
  
  /* NEW LINE */
  if ( recvfrom( sock, (void *)&from_msg, sizeof(from_msg), 0, (SA *) &fsin, &alen ) < 0 )
    err_sys( "recvfrom" );
  fsin4 = fsin;

  lines_active++;
  to_msg.info.factory_ID = lines_active;
  to_msg.info.capacity = (random() % 41) + 10;
  to_msg.info.duration = /*(random() % 5) + 1*/ 1;
  to_msg.info.produce = to_msg.info.capacity;

  sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin4, alen );
  
  /* NEW LINE */
  if ( recvfrom( sock, (void *)&from_msg, sizeof(from_msg), 0, (SA *) &fsin, &alen ) < 0 )
    err_sys( "recvfrom" );
  fsin5 = fsin;

  lines_active++;
  to_msg.info.factory_ID = lines_active;
  to_msg.info.capacity = (random() % 41) + 10;
  to_msg.info.duration = /*(random() % 5) + 1*/ 1;
  to_msg.info.produce = to_msg.info.capacity;

  sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin5, alen );
  
  while (!done) 
    {
      alen = sizeof(fsin);

      if ( recvfrom( sock, (void *)&from_msg, sizeof(from_msg), 0, (SA *) &fsin, &alen ) < 0 )
        err_sys( "recvfrom" );

      to_msg.info.factory_ID = from_msg.info.factory_ID;
      to_msg.info.capacity = from_msg.info.capacity;
      to_msg.info.duration = from_msg.info.duration;
      if (parts_remaining < 1) // if done
        {
          done = 1;
        }
      else if ((parts_remaining - from_msg.info.capacity) >= 0) // if this isn't last order
        {
          to_msg.info.produce = from_msg.info.capacity;
          parts_remaining -= from_msg.info.produce;
          total_produced += from_msg.info.capacity;
          sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin, alen );
        }
      else //if this is last order
        {
          to_msg.info.produce = parts_remaining;
          total_produced += parts_remaining;
          parts_remaining = 0;
          sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin, alen );
        }
    }
      
  to_msg.info.factory_ID = from_msg.info.factory_ID;
  to_msg.info.capacity = from_msg.info.capacity;
  to_msg.info.duration = from_msg.info.duration;
  to_msg.info.produce = 0;
      
  sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin1, alen );
  sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin2, alen );
  sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin3, alen );
  sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin4, alen );
  sendto( sock , (void *) &to_msg, sizeof(to_msg), 0, (SA *) &fsin5, alen );

  printf ("Parts Remaining: %d Total Produced: %d\n", parts_remaining, total_produced);
  printf ("Total items produced: %d\n", total_produced);
  while (1);
}

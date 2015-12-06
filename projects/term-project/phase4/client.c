#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h> 
#include <errno.h>

#include "mySock.h"
#define MAXBUFLEN   256

/*------------------------------------------------------------------------
 * main - UDP client for DAYTIME service that prints the resulting time
 *----------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    char	*host    = "localhost";    /* host to use if none supplied	*/
    char	*service = "daytime";      /* default service name	        */
    char    *msg     = "Bla Bla Bla" ;
    char    timeStr[MAXBUFLEN];        /* time string   */ 
    int	    s, n;                      /* socket descriptor, read count */

    switch (argc) 
    {
        case 1:
            break;
        case 3:
            service = argv[2];
            /* FALL THROUGH */
        case 2:
            host = argv[1];
            break;
        default:
            fprintf(stderr, "usage: %s [host [port]]\n" , argv[0] );
            exit(1);
    }
    s = clientUDPsock( host , service );  
    /* socket will always send to host:service */
    /* Therefore, use  in sendto( .... , NULL , 0) */
    
    fprintf(stderr , "DAYTIME client sending '%s'\n" , msg ) ;
    /* must send the \0 at end of msg, too */
    sendto( s, (void *) msg, strlen(msg)+1, 0, NULL, 0);
    
    n = recvfrom( s, (void*) timeStr, MAXBUFLEN, 0, NULL , 0 );
    if ( n <= 0 )
        err_sys( "Failed to get the daytime from the server" );

    timeStr[strlen(timeStr)-1] = 0 ; /* I hate the \n char placed by ctime_r() */
    printf( "DAYTIME client received %d chars in '%s'\n" , n , timeStr );
    exit(0);
}

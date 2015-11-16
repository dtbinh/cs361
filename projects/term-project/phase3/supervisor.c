#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "shmem.h"
#include "message.h"

int main( int argc , char *argv[] )
{
	int shmid, shmflg, queID, msgStatus;
	key_t shmkey, msgQueKey;
	shared_data *p;
	msgBuf msg;

	shmkey = SHMEM_KEY ;
	shmflg = IPC_CREAT | S_IRUSR | S_IWUSR  /* | IPC_EXCL */ ;

	shmid = shmget( shmkey , SHMEM_SIZE , shmflg );

	if (shmid == -1)
	{
		printf("\nFailed to create/find shared memory '0x%X'.\n", shmkey );
		perror("Reason:");
		exit(-1);
	}

	p = (shared_data *) shmat( shmid , NULL , 0 );
	if (p == (shared_data *) -1)
	{
		printf ("\nFailed to attach shared memory id=%d\n" , shmid );
		perror("Reason:");
		exit(-1) ;
	} 
  
  /* Create / Find the message queues */
  msgQueKey = BASE_MAILBOX_NAME ;
  queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/
  if ( queID < 0 )
  {
    printf("Failed to create mailbox %X. Error code=%d\n", msgQueKey , errno ) ;
    exit(-2) ;
  }
  
  /* Now, wait for a message to arrive from the User process */
  msgStatus = msgrcv( queID , &msg , MSG_INFO_SIZE , 1 , 0 );
  if ( msgStatus < 0 )
  {
    printf("Failed to receive message from User process on queuID %d. Error code=%d\n"
        , queID , errno ) ;
    exit(-2) ;
  }
  else
  {
    printf("Calculator received the following message from the User:\n" );
    printMsg( & msg );
    printf("\n");
  }

	return 0;
}

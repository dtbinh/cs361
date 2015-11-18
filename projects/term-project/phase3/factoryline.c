#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#include "shmem.h"
#include "message.h"

int
main( int argc , char *argv[] )
{
	int shmid, shmflg,
      queID, msgStatus,
      capacity, line_number, num_iters, produced, duration;
  msgBuf msg;
	key_t shmkey, msgQueKey;
	shared_data *p;

	capacity = atoi(argv[2]);
	line_number = atoi(argv[1]);
	num_iters = 0;
	produced = 0;
	duration = atoi(argv[3]);

	shmkey = SHMEM_KEY;
	shmflg = IPC_CREAT | S_IRUSR | S_IWUSR  /* | IPC_EXCL */;

	shmid = shmget( shmkey , SHMEM_SIZE , shmflg );

	if (shmid == -1)
	{
		printf("\nFailed to create/find shared memory '0x%X'.\n", shmkey );
		perror("Reason");
		exit(-1);
	}

	p = (shared_data *) shmat( shmid , NULL , 0 );
	if (p == (shared_data *) -1)
	{
		printf ("\nFailed to attach shared memory id=%d\n" , shmid );
		perror("Reason");
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

  /* prepare a message to send to the Calculator process */
  msg.mtype = 1; /* this is a "production" message type */
  msg.info.sender = getpid();
  msg.info.capacity = capacity;
  msg.info.duration = duration;
  msg.info.line_number = line_number;
  msg.info.num_iters = num_iters;
  msg.info.produced = produced;
  
  /* Send one message to the Supervisor process */
  msgStatus = msgsnd( queID , &msg , MSG_INFO_SIZE , 0 ) ; /* the msg flag is set to 0 */
  if ( msgStatus < 0 )
  {
    printf("Failed to send message to Calculator process on queuID %d. Error code=%d\n" , queID , errno ) ;
    exit(-2);
  }

	printf("Factory Line %d Capacity: %d\n", line_number, capacity);
	printf("Factory Line %d Duration: %d\n", line_number, duration);

	do
	{
		num_iters++;
		sem_wait(&(p->cntMutex));
		if(capacity < p->parts_remaining)
		{
			produced += capacity;
			p->parts_remaining -= capacity;
		}
		else
		{
			produced += p->parts_remaining;
			p->parts_remaining = 0;
		}
		sem_post(&(p->cntMutex));
		sleep(duration);
	}
	printf("Factory Line %d Total Iterations: %d\n", line_number, num_iters);
	printf("Factory Line %d Produced %d Items\n", line_number, produced);
	p->total += produced;
  // post semaphore to wake up parent if all work is done
	return 0;
}

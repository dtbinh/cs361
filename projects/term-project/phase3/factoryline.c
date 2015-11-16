#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "shmem.h"

int main( int argc , char *argv[] )
{
	int shmid, shmflg;
	key_t shmkey;
	shared_data *p;
	/* User arguments */
	int factoryID, capacity;
	double duration;

	int line_number = atoi(argv[0]);
	int numIters = 0;
	int produced = 0;
	capacity = atoi(argv[1]);
	duration = atol(argv[2]);

	shmkey = SHMEM_KEY ;
	shmflg = IPC_CREAT | S_IRUSR | S_IWUSR  /* | IPC_EXCL */ ;

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

	/*
	// Initialize both rendezvous semaphores
	// in the shared memory /   
	if( sem_init(&(p->client), 1, 0) )
	{
		perror("Failed to init client's semaphore");
		exit(-1) ;     
	}
	if(sem_init(&(p->server), 1, 0 ))
	{
		perror("Failed to init server's semaphore") ;
		exit(-1);
	}

	/ write to shared mem /
	p->d1 = atof( argv[1] );

	// awaken server       /
	if (sem_post(&(p->client)))
	{
		perror("Failed to post client's semaphore ");
		exit(-1);
	}
	printf("Cliet posted its semaphore\n");
	printf("Cliet now waits for server\n");

	if(sem_wait(&(p->server)))  / wait for server /
	{
		perror("Failed to wait for server's semaphore");
		exit(-1);
	}

	printf ("\nd1=%8.3f, d2=%8.3f\n", p->d1, p->d2 );

	// Destroy the shared semaphores. ONLY one process does it /
	if(sem_destroy(&(p->client)))
	{
		perror("Failed to destroy client's semaphore");
		exit(-1);
	}

	if(sem_destroy(&(p->server)))
	{
		perror("Failed to destroy server's semaphore");
		exit(-1);
	}

	// Destroy the shared memory segment /     
	shmdt(p);
	shmctl(shmid, IPC_RMID, NULL);
	printf("Client -- Goodbye\n");   
	*/
	
	printf("Factory Line %d Capacity: %d\n", line_number, capacity);
	printf("Factory Line %d Duration: %d\n", line_number, duration);

	do
	{
		numIters++;
		sem_wait(&cntMutex);
		if(capacity < parts_remaining)
		{
			produced += capacity;
			parts_remaining -= capacity;
		}
		else
		{
			produced += parts_remaining;
			parts_remaining = 0;
		}
		sem_post(&cntMutex);
		sleep(duration);
	}
	while(parts_remaining > 0);

	printf("Factory Line %d Total Iterations: %d\n", line_number, numIters);
	printf("Factory Line %d Produced %d Items\n", line_number, produced);
	total += produced;
	return 0;
}

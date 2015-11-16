#include <semaphore.h>

typedef struct {
	sem_t factory_lines_finished;
	int linesActive;
	double d1;
	double d2;    
} shared_data;

typedef struct {
	long mtype; /* 1: request, 2: reply */
	struct {
		pid_t sender;
	} info;
} msgBuf;

#define MSG_INFO_SIZE (sizeof(msgBuf) - sizeof(long))
#define BASE_MAILBOX_NAME 0x20

#define SHMEM_KEY  0x100
#define SHMEM_SIZE sizeof(shared_data)

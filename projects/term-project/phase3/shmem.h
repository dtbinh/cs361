#include <semaphore.h>

typedef struct {
	sem_t factory_lines_finished, cntMutex;
	int lines_active, parts_remaining, total;
} shared_data;

#define SHMEM_KEY  0x100
#define SHMEM_SIZE sizeof(shared_data)

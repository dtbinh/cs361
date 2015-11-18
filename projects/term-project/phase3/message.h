#include <sys/types.h>
#define MAXNAMELEN 20
typedef struct {
	long mtype ; 			/* 1: production , 2: termination */

	struct {
    pid_t sender; 		/* ID of sending process */
    int capacity,
        duration,
        line_number,
        num_iters,
        produced;
	} info; 
} msgBuf ;

#define MSG_INFO_SIZE ( sizeof(msgBuf) - sizeof(long) )
#define BASE_MAILBOX_NAME 0x20

void printMsg( msgBuf *m ) ;
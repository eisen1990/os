#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <sys/time.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define FALSE 0

/*
 *  If you want to use GLOBAL_LOCK, then set:
 *  GLOBAL_LOCK 1
 *
 *  If you want to use CURRENT_LOCK, then set:
 *  GLOBAL_LOCK 0
 */
#define GLOBAL_LOCK 1
#define THREAD_SIZE 20

typedef struct _Queue
{
	struct _Node *head;
	struct _Node *tail;
#if GLOBAL_LOCK == 1
	pthread_mutex_t lock;
#else
	pthread_mutex_t headlock;
	pthread_mutex_t taillock;
#endif
} Queue;


typedef struct _Node
{
	char *data;
	struct _Node *next;
} Node;

int InitQueue(Queue *q);
void FreeQueue(Queue *q);
void TrackQueue(Queue *q);
void Enqueue(Queue *q, char *value);
char* Dequeue(Queue *q);


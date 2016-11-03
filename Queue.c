#include <Queue.h>

int InitQueue(Queue *q)
{
	q->tail = q->head = malloc(sizeof(Node));
	q->tail->next = q->head->next = NULL;
#if GLOBAL_LOCK == 1
	pthread_mutex_init(&q->lock, NULL);
#else
	pthread_mutex_init(&q->headlock, NULL);
	pthread_mutex_init(&q->taillock, NULL);
#endif
	return 0;
}

void FreeQueue(Queue *q)
{
	Node *tmp = q->head->next;
	while(tmp != NULL)
	{
		tmp = tmp->next;
		free(tmp);
	}
}

void TrackQueue(Queue *q)
{
	Node *tmp = q->head;
	int i = 0;
	while(tmp = tmp->next)
	{
		printf("data : %s |", tmp->data);
		if(i++ > 9)
		{
			printf("\n");
			i = 0;
		}
	}
	printf("\nTrack End\n");
}

void Enqueue(Queue *q, char *value)
{
	Node *New = malloc(sizeof(Node));
	New->data = value;
	New->next = NULL;

#if GLOBAL_LOCK == 1
	pthread_mutex_lock(&q->lock);
#else
	pthread_mutex_lock(&q->taillock);
#endif
	q->tail->next = New;
	q->tail = New;
#if GLOBAL_LOCK == 1
	pthread_mutex_unlock(&q->lock);
#else
	pthread_mutex_unlock(&q->taillock);
#endif
}

char* Dequeue(Queue *q)
{
	char* ret = "ERROR";
#if GLOBAL_LOCK == 1
	pthread_mutex_lock(&q->lock);
#else
	pthread_mutex_lock(&q->headlock);
#endif
	Node *tmp = q->head->next;
	if(tmp == NULL)
	{
		//printf("Queue is emptry\n");
#if GLOBAL_LOCK == 1
	pthread_mutex_unlock(&q->lock);
#else
	pthread_mutex_unlock(&q->headlock);
#endif
		return ret;
	}
	q->head->next = tmp->next;
	ret = tmp->data;
#if GLOBAL_LOCK == 1
	pthread_mutex_unlock(&q->lock);
#else
	pthread_mutex_unlock(&q->headlock);

#endif
	free(tmp);
	tmp = NULL;

	return ret;
}

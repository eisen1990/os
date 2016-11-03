#include <Queue.h>
#define MAX_ENQ 10000000
volatile int T_A = MAX_ENQ;
volatile int T_B = MAX_ENQ;

Queue q;

void *Function_A(void *arg)
{
	while(T_A-- > 0)
	{
		Enqueue(&q, "data");
	}
	//printf("Thread A End\n");
	return NULL;
}

void *Function_B(void *arg)
{
	while(T_B-- > 0)
	{
		Dequeue(&q);
	}
	//printf("Thread B End\n");
	return NULL;
}

int main()
{
	clock_t before, after;
	double oper_time;
	int InitFlag = 1;
	int i = 0;
	int ThreadState;
	pthread_t En[THREAD_SIZE];
	pthread_t De[THREAD_SIZE];

	//printf("Startup Entry Point\n");
	InitFlag = InitQueue(&q);
	before = clock();
	while(InitFlag);
	for(i = 0; i < THREAD_SIZE; i++)
	{
	if(pthread_create(&En[i], NULL, Function_A, NULL)) exit(1);
	if(pthread_create(&De[i], NULL, Function_B, NULL)) exit(1);
	}
	
	for(i = 0; i < THREAD_SIZE; i++)
	{
	pthread_join(En[i], NULL);
	pthread_join(En[i], NULL);
	}

	//printf("Threads End, Start Free Queue\n");
	//TrackQueue(&q);
	after = clock();
	printf("time : %f sec\n",((double)(after - before) / CLOCKS_PER_SEC));
	FreeQueue(&q);
	//printf("Free Queue End, Process end\n");
	return 0;
}

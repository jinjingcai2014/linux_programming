#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define   NUM   5
int  queue[NUM];
sem_t   blank_num,  product_num;

void *producer(void  *arg)
{
	int  p = 0;
	while(1){
		sem_wait(&blank_num);
		queue[p] = rand() % 1000+1;
		printf("Producer %d \n", queue[p]);
		sem_post(&product_num);
		p = (p+1) %NUM;
		sleep(rand() %NUM);
	}
}

void  *consumer(void *arg)
{
	int   c = 0;
	while(1){
		sem_wait(&product_num);
		printf("Consumer  %d\n", queue[c]);
		queue[c] = 0;
		sem_post(&blank_num);
		c = (c+1)%NUM;
		sleep(rand() %5);
	}
}
int   main(int  argc,   char *argv[])
{
	pthread_t  pid,  cid;

	sem_init(&blank_num,  0,  NUM);
	sem_init(&product_num,  0,   0);
	pthread_create(&pid,  NULL,   producer,  NULL);
	pthread_create(&cid,   NULL,   consumer, NULL);
	pthread_join(pid,  NULL);
	pthread_join(cid,   NULL);
	sem_destroy(&blank_num);
	sem_destroy(&product_num);
	return 0;
}
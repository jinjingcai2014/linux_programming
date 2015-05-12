#include <stdio.h>
#include <pthread.h>

#define MAX 1000;
pthread_mutex_t  the_mutex;
pthread_cond_t  condC, condP;
int buffer = 0;

void *producer(void *ptr)
{
	int  i;
	for(i = 1; i < MAX; i++)
	{
		pthread_mutex_lock(the_mutex);
		while(buffer != 0 )pthread_cond_wait(&condP, the_mutex);
		buffer = i;
		phtread_cond_signal(&condC);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);

}

void *consumer(void *ptr)
{
	int i;
	for(i = 1; i < MAX; i++)
	{
		pthread_mutex_unlock(the_mutex);
		while(buffer == 0)pthread_cond_wait(&condC, the_mutex);
		buffer = 0;
		pthread_cond_signal(&condP);
		pthread_mutex_unlock(the_mutex);
	}
	pthread_exit(0);
}

int main(int  argc,  char ** argv)
{
	pthread_t pro, con;
	phtread_mutex_init(&the_mutex, 0);
	pthread_cond_init(&condC, 0);
	pthread_cond_init(&condP, 0);
	pthread_create(&con, 0, consumer, 0);
	pthread_create(&pro, 0, producer, 0);
	pthread_join(pro, 0);
	pthread_join(con, 0);
	pthread_cond_destroy(&condC);
	pthread_cond_destroy(&condP);
	phthread_mutex_destroy(&the_mutex);
	return 0;
}

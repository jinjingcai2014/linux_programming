#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define   MAXLINE  3
int  constcounter, t;
pthread_mutex_t   deadlockA, deadlockB;
pthread_t  pthreadId[3];

void  *fun_do_2(void *arg)
{
	printf("run to pthread 2 \n");
	printf("pid = %u,  2pthreadId2 = %u\n",(unsigned int )getpid(),  (unsigned int )pthread_self());
	pthread_mutex_lock(&deadlockB);
	
	
	printf("begin to get lockA\n");
	printf("run pthread 2222222\n");
	pthread_mutex_lock(&deadlockA);
	
	printf("end  lock A B\n");
	pthread_mutex_unlock(&deadlockB);
	pthread_mutex_unlock(&deadlockA);
	
           
}
void * fun_do1 (void * arg)
{

    	printf("run to pthread 1\n");
	
	printf("pid = %u,  1pthread Id1 = %u\n", (unsigned int)getpid(),  (unsigned int )pthread_self());
	printf("begin to get lockA\n");
	pthread_mutex_lock(&deadlockA);

	pthread_create(&pthreadId[2], NULL,  fun_do_2, NULL);  
	printf("begin to get lockB\n");
	printf("Pthread 1 1111\n");
	pthread_mutex_lock(&deadlockB);

	pthread_join(pthreadId[2], NULL);
	pthread_mutex_unlock(&deadlockA);
	pthread_mutex_unlock(&deadlockB);
	printf("end to unlock lockA lockB");
	
	
}



int main(int argc, char const *argv[])
{
	
	constcounter = 0;
	int pthreadno1;
	
	int i;
	
	pthread_mutex_init(&deadlockA, NULL);
	pthread_mutex_init(&deadlockB, NULL);
	
	
	
	printf("Main   begin to create pthread A\n");
	pthreadno1 = pthread_create(&pthreadId[1], NULL, fun_do1, NULL);
	printf("pthreadno1 = %d\n", pthreadno1);
	
	printf("Main  begin to create to pthread B\n");
	
	
	
	
	for( i = 1; i < MAXLINE -1; i ++)
		pthread_join(pthreadId[i], NULL);
	pthread_mutex_destroy(&deadlockB);
	pthread_mutex_destroy(&deadlockA);

	return 0;
}
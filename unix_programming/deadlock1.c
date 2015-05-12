#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


int  constcounter, t;
pthread_rwlock_t   deadlockA, deadlockB;
void *fun_do_1(void * arg)
{
	
	printf("run  to 1111111");
	printf("1pid = %u", (unsigned int)getpid());
	printf("1pthread Id = %u\n", (unsigned int )pthread_self());
	printf("1begin to get lockA\n");
	pthread_rwlock_wrlock(&deadlockA);
	
	sleep(5);
	printf("1 begin to get lockB\n");

	pthread_rwlock_wrlock(&deadlockB);
	

	pthread_rwlock_unlock(&deadlockA);
	pthread_rwlock_unlock(&deadlockB);
	printf("1end to unlock lockA lockB");

}

void  *fun_do_2(void *arg)
{
	printf("2222\n");
	printf("2pid = %u, pthreadId = %u\n",(unsigned int )getpid(),  (unsigned int )pthread_self());
	
	pthread_rwlock_wrlock(&deadlockB);
	
	printf("2begin to get lockA\n");
	pthread_rwlock_wrlock(&deadlockA);
	
	printf("2end  lock A B\n");
	pthread_rwlock_unlock(&deadlockB);
	pthread_rwlock_unlock(&deadlockA);
	

}

int main(int argc, char const *argv[])
{
	
	constcounter = 0;
	int pthreadno1, pthreadno2 ;
	
	
	pthread_rwlock_init(&deadlockA, NULL);
	pthread_rwlock_init(&deadlockB, NULL);
	
	pthread_t  pthreadId[3];
	
	printf("Main   begin to create pthread A\n");
	pthreadno1 = pthread_create(&pthreadId[1], NULL, fun_do_1, NULL);
	printf("pthreadno1 = %d\n", pthreadno1);
	
	printf("Main  begin to create to pthread B\n");

	pthreadno2 = pthread_create(&pthreadId[2], NULL,  fun_do_2, NULL); 
	printf("constcounter = %d\n", constcounter);
	
	pthread_rwlock_destroy(&deadlockB);
	pthread_rwlock_destroy(&deadlockA);


	pthread_join(pthreadId[1], NULL);
	pthread_join(pthreadId[2], NULL);
	return 0;
}
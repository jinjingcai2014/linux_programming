#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int i = 0;
	pthread_mutex_t  deadlockA, deadlockB;
	pthread_mutex_init(&deadlockA, NULL);
	pthread_mutex_init(&deadlockB, NULL);
	pthread_mutex_lock(&deadlockA);
	for(i = 0; i < 12; i++){
	i += 3;
	}
	printf("i = %d\n", i);
	printf("get  lockA  \n");
	pthread_mutex_lock(&deadlockA);
	printf("print i again:\n");
	printf("%d\n", i);
	pthread_mutex_unlock(&deadlockA);
	return 0;
}
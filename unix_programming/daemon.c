#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
int fd;
void daemonize(void )
{
	pid_t  pid;
	
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}else if(pid != 0){
		exit(0);
	}

	setsid();

	if(chdir("/") < 0){
		perror("chdir");
		exit(2);
	}
/*set mask*/
	umask(0);

	close(0);
	//open("/home/caijingjin/dameon.log", O_RDWR|O_CREAT|O_APPEND);
	fd = open("/home/caijingjin/dameon.log", O_RDWR|O_CREAT|O_APPEND);
		
	//dup2(0, 1);
	//dup2(0,  2);
}
int main(int argc, char const *argv[])
{
		
	daemonize();
	while(1){
		
		char *buf;
		time_t  a;
		time(&a);
		ctime_r(&a, buf);
		write(fd, buf, strlen(buf));

		sleep(10);
	}
	return 0;
}
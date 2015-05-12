#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(void )
{
	int  fd[2];
	char  str[] = "hello computer!\n";
	pid_t  pid;
	char  buf[1024];

	if(pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	//father write son read
	/***
	fd[0] = 3  read
	fd[1] = 4  write
	**/
	pid = fork();
	if(pid > 0)
	{
		close(fd[0]);
		sleep(2);
		write(fd[1],  str,  strlen(str));
		wait(NULL);
	}

	else if(0 == pid)
	{
		int len;
		close(fd[1]);
		len = read(fd[0], buf , sizeof(buf));
		write(STDOUT_FILENO, buf, len);
	}
	else{
		perror("fork");
		exit(1);
	}
	return 0;
}
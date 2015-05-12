#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#define MAXLINE    80

int main()
{
	int n,flags;
	int fd[2];
	pid_t pid;
	char line[MAXLINE];

	if(pipe(fd) < 0){
		perror("pipe\n");
		exit(1);
	}

	if((pid = fork()) <0){
		perror("fork\n");
		exit(1);
	}

	if(pid > 0){
		close(fd[0]);
		write(fd[1], "hello World\n", 12);
		wait(NULL);
	}
	else{
		close(fd[1]);
tryagain:
		flags = fcntl(fd[0], F_GETFL);
		flags |= O_NONBLOCK;
		fcntl(fd[0], F_SETFL, flags);

		n = read(fd[0], line, MAXLINE);
		if( -1 == n){
			if( errno == EAGAIN)
				write(STDOUT_FILENO, "try again\n",10);
			sleep(1);
			goto tryagain;
		}
		else{
			perror("read");
			exit(1);
		}
		write(STDOUT_FILENO, line, n);
	}
	return 0;
}
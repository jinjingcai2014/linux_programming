#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXLINE    80

int main()
{
	int n;
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
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
	}
	return 0;
}
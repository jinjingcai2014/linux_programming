#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void sys_err(char *str, int exitno)
{
	perror(str);
	exit(exitno);
}

int main(int argc , const char *argv[])
{
	int fd,n;
	char buf[1024] = "hello caijingjin\n";

	if(argc < 2)
	{
		printf("./a.out   filename\n");
		exit(1);
	}
	
while(1){
	fd = open(argv[1], O_RDONLY);
	if(fd < 0) sys_err("open", 1);
	n = read(fd, buf, strlen(buf));
	if(n < 0 )
		sys_err("read", 2);
	printf("strlen(buf) = %d\n",strlen(buf));
	write(STDOUT_FILENO, buf, n);
	close(fd);
}
	return 0;
}
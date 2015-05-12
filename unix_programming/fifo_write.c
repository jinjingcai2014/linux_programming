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
	int fd;
	char buf[1024] = "hello caijingjin\n";

	if(argc < 2)
	{
		printf("./a.out   filename\n");
		exit(1);
	}
	

	fd = open(argv[1], O_RDWR);
	if(fd < 0) sys_err("open", 1);
	write(fd, buf, strlen(buf));
	//printf("sizeof(buf) = %d\n",strlen(buf));
	close(fd);
	return 0;
}
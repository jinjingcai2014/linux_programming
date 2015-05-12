#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	/* code */
	char *p ;
	int fd, len;
	fd = open("mmap_helloworld", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
	len = lseek(fd, 0, SEEK_END);
	p = (char*)mmap(NULL,len, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
	if( p == MAP_FAILED){
		perror("mmap");
		exit(1);
	}
	close(fd);
	int i;
	puts(p);
	p[0] = 'I';
	p[1] = 'A';
	p[2] = 'M';
	munmap(p, len);
	return 0;
}
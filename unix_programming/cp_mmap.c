#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define  FILE_MODE  (S_IRUSR| S_IWUSR|S_IRUSR | S_IROTH) 
int  main(int  argc,  char *argv[ ])
{
	int  fdin, fdout;
	void  *src, *dst;
	struct  stat  statbuf;

	if(argc != 3)
		perror("usage: <fromfile>  <tofile>");
	if((fdin = open(argv[1], O_RDONLY)) < 0)
		perror("cann't  open fail  for reading\n");
	
	if((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC , FILE_MODE)) < 0)
		perror("cann't  create a file for writing\n");

	if(fstat(fdin, &statbuf) < 0 )
		perror("fstat error");

	if(lseek(fdout, statbuf.st_size  -1, SEEK_SET) == -1)
		perror("lseek  error");
	if(write(fdout, "", 1)  != 1)perror("writing  error");

	if((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED)
		perror("mmap  error  for  input");
	if((dst = mmap(0, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fdout,0)) == MAP_FAILED)
		perror("mmap  error for  output");
	memcpy(dst, src, statbuf.st_size);
	return 0;

}
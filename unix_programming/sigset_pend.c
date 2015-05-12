#include <stdio.h>
#include <signal.h>

void printsigset(const  sigset_t  *set)
{
	int  i;
	for(i = 1; i < 32;  i ++)
		if(sigismember(set,  i) == 1)
			putchar('1');
		else 
			putchar('0');
	puts("");//printf("\n")

}
int main(int argc, char const *argv[])
{
	sigset_t  s, p;
	sigemptyset(&s);
	sigaddset(&s, SIGQUIT);
	sigprocmask(SIG_BLOCK, &s, NULL);
	while(1){
		sigpending(&p);
		printsigset(&p);
		sleep(1);
	}
	return 0;
}

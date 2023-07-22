// test signal and pause
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <cstdlib>
void do_nothing(int sig)
{
	return;
}
int main()
{
	pid_t pid;
	signal(SIGVTALRM, do_nothing);
	pid = fork();
	if (pid == 0)
	{
		pause();
		printf("child\n");
		_exit(0);
	}
	else
	{
		printf("parent\n");
		sleep(2);
		kill(pid, SIGVTALRM);
	}
	wait(NULL);
	printf("parent exiting\n");
	sleep(2);
	return 0;
}

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(void){
	pid_t pid;
	pid = getpid();
	printf("%d ", pid);
	pid = getppid();
	printf("%d", pid);
	return 0;
}

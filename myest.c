#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

struct message {	
       	long type;
	char str[1];
};
int judge(int msgid,  int N){
	struct message ms;
	struct message est;
	struct message end;
	est.type = N + 1;
	end.type = 2 * N + 2;
	for (int i = 1; i < N + 1; i++){
        	msgrcv(msgid, &ms, 1, i, 0);
		sync();
       	}
	printf("J : All runners are ready to run\n");
	sync();
	msgsnd(msgid, &est, 1, 0);
	printf("J : Stick passed to 1 runner\n");
	sync();
	msgrcv(msgid, &ms, 1, 2 * N + 1, 0);
	printf("J : Stick taken from last runner\n");
	sync();
	printf("J : Competition ended. All runners can go home\n");
	sync();
	for (int i = 0; i < N; i++)
	{
        	msgsnd(msgid, &end, 1, 0);
	}
	return 0;
}
int runners(int msgid,int i, int N){
	struct message red;
	struct message ms;
	struct message est;
	est.type = N + i + 1;
	red.type = i;
	msgsnd(msgid, &red, 1, 0);	
    	printf("%d R :I'm Ready.\n", i);
	sync();
	msgrcv(msgid, &ms, 1, N + i, 0);
	printf("%d R :I got stick.\n", i);
	sync();
	msgsnd(msgid, &est, 1, 0);
    	if (i != N){
		printf("%d R : Stick passed to runner %d\n", i, i + 1);
		sync();
	}else{
		printf("%d R : Stick passed to judge\n", i);
		sync();
	}
	msgrcv(msgid, &red, 1, 2 * N + 2, 0);
	printf("%d R: Thanks for competiton. Good bye \n", i); 
	sync();
	return 0;
}
int main (int argc, char* argv[]){
	int n = 0;
	int N = atoi(argv[1]);
	pid_t pid;
	int id = msgget(IPC_PRIVATE, IPC_CREAT | 0600);
	printf("C:  Created message queue with id %d.\n", id);
	pid = fork();
	if (pid == 0)
	{
		judge(id, N);
		return 0;
	}

	for (int i = 1; i < N + 1; i++){
        	pid = fork();
        	if (pid == 0){
            		runners(id, i, N);
            		return 0;
        	}
    	}
	for (int i = 0; i < N + 1; i++)
	{
        	wait(&n);	
	}
	msgctl(id, IPC_RMID, 0);
	printf("C: Queue removed with %d \n", id);
	return 0;
}

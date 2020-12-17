#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define SVMSG_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define MSG "/home/zetsu/lab4/queue/msg"

struct msgbuf
{
	long mtype;
	char mtext[1];
};

void	create_msg()
{
	msgget(ftok(MSG, 0), SVMSG_MODE | IPC_CREAT);
	printf("SERVER created queue in %s\n", MSG);
}

void	send_msg(int len, long type)
{
	int mqid;
	struct msgbuf buff;

	mqid = msgget(ftok(MSG, 0), S_IWUSR);
	//ptr = (struct msgbuf*) calloc(sizeof(long) + len, sizeof(char));
	buff.mtype = type;
	msgsnd(mqid, &buff, len, 0);
	printf("SERVER sent message with type %ld\n", buff.mtype);
}

int		main(int argc, char **argv)
{
	create_msg();
	send_msg(1, 101);
	send_msg(2, 202);
	send_msg(3, 303);
	return 0;
}

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
#define MAXMSG (8192 + sizeof(long))

struct msgbuf
{
	long mtype;
	char mtext[1];
};

void	del_msg()
{
	int mqid;

	mqid = msgget(ftok(MSG, 0), 0);
	msgctl(mqid, IPC_RMID, NULL);
	printf("Deleted queue\n");
}

int		main()
{
	int mqid;
	long type = 0;
	long flag = 0;
	struct msgbuf buff;
	ssize_t n;

	//buff = (struct msgbuf*) malloc(MAXMSG);
	mqid = msgget(ftok(MSG, 0), S_IRUSR | S_IRGRP | S_IROTH);
	while (1)
	{
		sleep(1);
		n = msgrcv(mqid, &buff, MAXMSG, type, flag);
		if (buff.mtype != 0)
			printf("CLIENT recieved message from SERVER, read %ld bytes, with type - %ld\n", n, buff.mtype);
		if (buff.mtype == 303)
			break;
	}
	del_msg();
	return 0;
}

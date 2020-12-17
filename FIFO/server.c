#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO1 "/home/zetsu/lab4/FIFO/fifo.1"
#define FIFO2 "/home/zetsu/lab4/FIFO/fifo.2"
#define MAXLINE 128
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char **argv)
{
	int readfd = -1;
	int writefd = -1;
	ssize_t n = 0;
	char str[MAXLINE];

	unlink(FIFO1);
	unlink(FIFO2);
	mkfifo(FIFO1, FILE_MODE);
	mkfifo(FIFO2, FILE_MODE);
	writefd = open(FIFO2, O_WRONLY);
	if (writefd != -1)
	{
		strcpy(str, "Message from SERVER");
		write(writefd, str, strlen(str));
		readfd = open(FIFO1, O_RDONLY);
		while ((n = read(readfd, str, MAXLINE)) > 0)
		{
			str[n] = 0;
			printf("SERVER recieved %s from CLIENT\n", str);
			break;
		}
		close(readfd);
		close(writefd);
		unlink(FIFO1);
		unlink(FIFO2);
	}
	return 0;
}

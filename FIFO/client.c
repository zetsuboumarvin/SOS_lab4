#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define FIFO1 "/home/zetsu/lab4/FIFO/fifo.1"
#define FIFO2 "/home/zetsu/lab4/FIFO/fifo.2"
#define MAXLINE 128

int main(int argc, char **argv)
{
	int readfd = -1;
	int writefd = -1;
	ssize_t n = 0;
	char str[MAXLINE];

	while (1)
	{
		readfd = open(FIFO2, O_RDONLY, 0);
		if (readfd != -1)
		{
			while ((n = read(readfd, str, MAXLINE)) > 0)
			{
				str[n] = 0;
				printf("CLIENT received message - %s\n", str);
				break;
			}
			writefd = open(FIFO1, O_WRONLY, 0);
			strcpy(str, "OK");
			write(writefd, str, strlen(str));
			close(readfd);
			close(writefd);
			break;
		}
	}
}

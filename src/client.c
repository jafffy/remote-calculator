#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#ifndef BOOL
#define BOOL int
#endif // BOOL

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef FALSE
#define FALSE 0
#endif // FALSE

enum State { Greeting, Transaction, Closing };


int main(int argc, char** argv)
{
	int sockfd, n;
	char sendline[100];
	char recvline[100];
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port	= htons(22000);

	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	enum State currentState = Greeting;
	BOOL isRunning = TRUE;

	while (isRunning) {
		bzero(sendline, 100);
		bzero(recvline, 100);
		fgets(sendline, 100, stdin);

		write(sockfd, sendline, strlen(sendline) + 1);
		read(sockfd, recvline, 100);

		if (currentState == Greeting && strncmp(recvline, "Start", 5) == 0) {
			printf("Greeted!\n");
			currentState = Transaction;
		}

		else if (currentState == Transaction && strncmp(recvline, "End", 3) == 0) {
			printf("Closing!\n");
			currentState = Closing;
			isRunning = FALSE;
		}

		else if (currentState == Transaction) {
			printf("%s\n", recvline);
		}
	}

	return 0;
}

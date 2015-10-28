#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "common.h"

int main()
{
	char str[100];
	int listen_fd, comm_fd;

	struct sockaddr_in servaddr;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(22000);

	bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	listen(listen_fd, 10);

	comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

	enum State clientState = Greeting;
	BOOL isRunning = TRUE;

	while (isRunning) {
		bzero(str, 100);

		read(comm_fd, str, 100);

		int lhs, rhs, res = 0;
		int ret;

		if (clientState == Greeting) {
			if (strncmp(str, "hello", 5)) {
				sprintf(str, "400 You didn't greet");
			} else {
				sprintf(str, "Start");
				clientState = Transaction;
			}
		} else if (strncmp(str, "add", 3) == 0) {
			ret = sscanf(str + 3, "%d %d", &lhs, &rhs);
			// TODO : When this result become overflow or underflow,
			// What happen? and how to fix it?
			res = lhs + rhs;

			if (res < -999999999 || res > 999999999) {
				sprintf(str, "500 Overflow");
			} else if (ret >= 2) {
				sprintf(str, "%d", res);
			} else {
				sprintf(str, "402 Too few Parameters");
			}
		} else if (strncmp(str, "sub", 3) == 0) {
			sscanf(str + 3, "%d %d", &lhs, &rhs);
			sprintf(str, "%d", lhs - rhs);
		} else if (strncmp(str, "mult", 4) == 0) {
			sscanf(str + 3, "%d %d", &lhs, &rhs);
			sprintf(str, "%d", lhs * rhs);
		} else if (strncmp(str, "div", 3) == 0) {
			sscanf(str + 3, "%d %d", &lhs, &rhs);
			sprintf(str, "%d", lhs / rhs);
		} else if (clientState == Transaction
					&&  strncmp(str, "quit", 4) == 0) {
			sprintf(str, "End");
			write(comm_fd, str, strlen(str) + 1);

			isRunning = FALSE;

			continue;
		} else {
			sprintf(str, "401 Unknown command");
		}

		write(comm_fd, str, strlen(str) + 1);
	}

	return 0;
}

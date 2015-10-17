#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define IP "127.0.0.1"
#define PORT 8888

enum E_STATUS_CODE {
	ESC_GOOD 		= 200,
	ESC_NOTGREETED 	= 400,
	ESC_NOTDEFINED	= 401,
	ESC_LESSOPRAND	= 402,
	ESC_NOTFITOPRD	= 403,
	ESC_OVERFLOWED	= 500
};

void error_handling(const char* message);

int main(int argc, char** argv)
{
	int sock;
	char message[BUFSIZ];
	int str_len;
	struct sockaddr_in serv_addr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family 		= AF_INET;
	serv_addr.sin_addr.s_addr 	= inet_addr(IP);
	serv_addr.sin_port 			= htons(PORT);

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("connect() error!");
	}

	while (1) {
		fgets(message, BUFSIZ, stdin);

		if (!strcmp(message, "q\n")) break;
		write(sock, message, strlen(message));
		printf("write\n");
		str_len = read(sock, message, BUFSIZ - 1);
		message[str_len] = 0;
		printf("read\n");
		fprintf(stdout, "%s\n", message);
	}

	close(sock);

	return 0;
}

void error_handling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);

	exit(1);
}

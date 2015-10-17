#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8888

void error_handling(const char* message);

int main(int argc, char** argv)
{
	int serv_sock, clnt_sock;
	char message[BUFSIZ];
	int str_len;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1) {
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT);

	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("bind() error");
	}

	if (listen(serv_sock, 5) == -1) {
		error_handling("listen() error");
	}

	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	printf("accpted\n");

	if (clnt_sock == -1) {
		error_handling("accept() error");
	}

	while ( (str_len = read(clnt_sock, message, BUFSIZ)) != 0 ) {
		printf("read\n");
		write(clnt_sock, message, str_len);
		write(1, message, str_len);
		printf("wrote\n");
	}

	close(clnt_sock);

	return 0;
}

void error_handling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);

	exit(1);
}

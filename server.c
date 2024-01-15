#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include"socket_helper.h"

int  bind_socket(int sock_fd);

int main(int argc, char *argv[]){

	int  sock_fd;
	int  client_fd;
	char message[MSG_SIZE];

	struct    sockaddr_in client;
	socklen_t clen = sizeof(client);

	printf("Server program..."NEW_LINE);
	check_error( -1, sock_fd = create_socket(), "socket() failed");
	check_error( -1, bind_socket(sock_fd),      "bind() failed");
	check_error( -1, listen(sock_fd, BACKLOG),  "listen() failed");

	while (1) {

		memset(&client,  0, clen);
		memset(&message, 0, MSG_SIZE);

		client_fd = accept(sock_fd, (struct sockaddr *)&client, (socklen_t *)&clen);
		check_error( -1, client_fd,  "accept() failed");
		printf("Connection accepted for %s\n", inet_ntoa(client.sin_addr));

		if (recv(client_fd, message, MSG_SIZE, 0) < 0) {
			perror("recv() ");
			close(client_fd);
			close(sock_fd);
			exit(EXIT_FAILURE);
		}
		printf("client-%s$ %s"NEW_LINE, inet_ntoa(client.sin_addr), message);
		memset(&message, 0, MSG_SIZE);

		strcpy(message, "Server connected");
		if (send(client_fd, message, sizeof(message), 0) < 0){
			perror("send() ");
			close(client_fd);
			close(sock_fd);
			exit(EXIT_FAILURE);
		}
		close(client_fd);
	}
	close(sock_fd);
	return 0;
}

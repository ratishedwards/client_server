#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include"socket_helper.h"

int socket_connect(int sock_fd);

int main(){

	int  sock_fd;
	char message[MSG_SIZE];

	printf("Client program..."NEW_LINE);
	check_error( -1, sock_fd = create_socket(), "socket() failed");
	check_error( -1, socket_connect(sock_fd),   "connect() failed");

	memset(message, 0, MSG_SIZE);
	strcpy(message, "Sending connection request");

	check_error(-1, set_socket_timeout_options(sock_fd), "set socket option failed");

	if (send(sock_fd, message, MSG_SIZE, 0) < -1){
		perror("recv() ");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}

	memset(message, 0, MSG_SIZE);
	if (recv(sock_fd, message, MSG_SIZE, 0) < -1){
		perror("recv() ");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	printf("Server$ %s"NEW_LINE, message);
	close(sock_fd);
	return 0;
}

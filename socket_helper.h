#ifndef _SOCKET_HELPER_H_
#define _SOCKET_HELPER_H_

#define NEW_LINE "\n"
#define BACKLOG 5
#define MSG_SIZE 128

void check_error(int success_condition, int condition, char *msg);
int  create_socket();
int  bind_socket(int sock_fd);
int  socket_connect(int sock_fd);
int  set_socket_timeout_options(int sock_fd);

int create_socket(){
	return socket(AF_INET, SOCK_STREAM, 0);
}

int bind_socket(int sock_fd){
	int port = 90190;
	struct sockaddr_in server_addr = {0};

	server_addr.sin_family  = AF_INET;
	server_addr.sin_port    = htons(port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	return bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
}

void check_error(int fail_condition, int condition, char *msg){
	if ( condition == fail_condition ){
		printf("Error : %s"NEW_LINE, msg);
		exit(EXIT_FAILURE);
	}
	return;
}

int socket_connect(int sock_fd){
	int ret_val = -1;
	int port  = 90190;
	struct sockaddr_in server = {0};

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	ret_val = connect(sock_fd, (struct sockaddr *)&server, sizeof(server));

	return ret_val;
}

int  set_socket_timeout_options(int sock_fd){
	struct timeval tv;
	tv.tv_sec  = 2;
	tv.tv_usec = 0;

	if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) < 0){
		printf("set SO_RCVTIMEO failed"NEW_LINE);
		return -1;
	}

	if (setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv)) < 0){
		printf("set SO_SNDTIMEO failed"NEW_LINE);
		return -1;
	}

	return 0;
}
#endif

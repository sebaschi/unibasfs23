// tcp/chat-client.c
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXPENDING 10
#define BUFSIZE 512
#define STDPORT 8080

int server(char *, char);

int main(int argc, char **argv)
{
	//NEW SOCKET DESCRIPTOR
	int tcp_socket = socket(PF_INET, SOCK_STREAM, 0);
	printf(">New TCP socket \n\n");

	//Check if Arguments given at start of program
	if(argc < 3) {
		server(argv[1], 'd');
	}
	else {
	}
	
}

int server(char *port, char s){
	int servSock = socket(PF_INET, SOCK_STREAM, 0);
	printf("New Server TCP Socket\n\n");

	//Configure Address in "server mode"
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(atoi(port));
	if (s == 's') {
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	} else {
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	}
	printf("Server Configured at IP %s\n\n",inet_ntoa(servAddr.sin_addr));

	// Bind
	bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr));
	printf("Socket and Address Config Bound.\n\n"); 

	// Listen until client arrives
	listen(servSock, MAXPENDING);
	printf("Started Listening on Port %u\n\n", ntohs(servAddr.sin_port));

	struct sockaddr_in cltAddr;
	socklen_t cltAddrLen = sizeof(cltAddr);
	int cltSock;
	printf("Allocated Client Address\n\n");
	
	cltSock = accept(servSock, (struct sockaddr*) &cltAddr, &cltAddrLen);
	printf("New client Accepted");

	char buf[BUFSIZE];
	int bytesRecv;

	return 1;

}

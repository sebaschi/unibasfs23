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

int main(int argc, char **argv)
{
	//NEW SOCKET DESCRIPTOR
	int tcp_socket = socket(PF_INET, SOCK_STREAM, 0);
	printf(">New TCP socket \n\n");

	//Configure Networking Family
	struct sockaddr_in addr; 
	addr.sinn_family = AF_INET;

	//Read in IPv4 addr as string from argv, convert to binary format and assign to;

}

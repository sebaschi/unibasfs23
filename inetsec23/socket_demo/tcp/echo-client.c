// tcp/echo-client.c

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define   RECEIVER_PORT   4242
#define   RECEIVER_IP     "127.0.0.1"

#define   BUFSIZE         512

int main() {

    // NEW SOCKET DESCRIPTOR
    int localSock = socket(PF_INET, SOCK_STREAM, 0);
    printf("> New TCP Socket\n\n");


    // ADDRESS CONFIGURATION (LOCAL)
    struct sockaddr_in localAddr;
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(0);
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("> Local Address Configured\n\n");


    // BINDING
    bind(localSock, (struct sockaddr*) &localAddr,sizeof(localAddr));
    printf("> Bound\n\n");


    // ADDRESS CONFIGURATION (REMOTE)
    struct sockaddr_in srvAddr;
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(RECEIVER_PORT);
    srvAddr.sin_addr.s_addr = inet_addr(RECEIVER_IP);
    printf("> Remote Address Configured\n\n");


    // CONNECTING
    connect(localSock, (struct sockaddr*) &srvAddr, sizeof(srvAddr));
    printf("> Connected\n\n");


    // SEND BUFFER
    char msg[] = "Ping-Pong Message!";
    send(localSock, msg, strlen(msg), 0);
    printf("> Sent Message\n\n");


    // RECEIVE AND ECHO
    char buf[BUFSIZE];
    int bytesRecv;
    bytesRecv = recv(localSock, buf, BUFSIZE, 0);
    while(bytesRecv > 0) {
        char segmentRecv[bytesRecv];
        strncpy(segmentRecv, buf, bytesRecv);
        printf("> Received Echo (%d bytes): %s\n\n", bytesRecv, segmentRecv);
        bytesRecv = recv(localSock, buf, BUFSIZE, 0);
    }



    return 0;

}

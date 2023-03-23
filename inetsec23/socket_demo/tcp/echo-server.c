// tcp/echo-server.c

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define   MAXPENDING   10
#define   BUFSIZE     512
#define   SERV_PORT  4242

int main() {
    

    // NEW SOCKET DESCRIPTOR
    int servSock = socket(PF_INET, SOCK_STREAM, 0);
    printf("> New TCP Socket\n\n");


    // ADDRESS CONFIGURATION (LOCAL)
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERV_PORT);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("> Local Address Configured\n\n");


    // BINDING
    bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr));
    printf("> Bound\n\n");


    // LISTENING
    listen(servSock, MAXPENDING);
    printf("> Listening\n\n");


    // CONNECTION-ACCEPTANCE-LOOP
    printf("> Start Looping...\n\n");
    for(;;) {
        struct sockaddr_in cltAddr;
        socklen_t cltAddrLen = sizeof(cltAddr);
        int cltSock;
        printf("> Client Address Allocated\n\n");

        // ACCEPT
        printf("> Pick a pending connection or wait...\n\n");
        cltSock = accept(servSock, (struct sockaddr*) &cltAddr, &cltAddrLen);
        printf("> New Connection Accepted\n\n");


        // PREPARE BUFFER
        char buf[BUFSIZE];
        int bytesRecv;


        // RECEIVE AND ECHO
        bytesRecv = recv(cltSock, buf, BUFSIZE, 0);
        while(bytesRecv > 0) {
            char segmentRecv[bytesRecv];
            strncpy(segmentRecv, buf, bytesRecv);
            printf("> Received %d bytes: %s\n\n", bytesRecv, segmentRecv);
            send(cltSock, buf, bytesRecv, 0); // ECHO
            printf("> Sent %d bytes: %s\n\n", bytesRecv, segmentRecv);
            bytesRecv = recv(cltSock, buf, BUFSIZE, 0);
        }

        // CLOSE
        close(cltSock);
        printf("> Closed Connection\n\n");

    }

}

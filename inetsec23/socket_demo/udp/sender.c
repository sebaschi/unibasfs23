// udp/sender.c

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define   RECEIVER_PORT   8888
#define   RECEIVER_IP     "127.0.0.1"
#define   BUFLEN          12

/*** UDP SENDER ***/
int main() {

    printf("- - - - - - - - - - - - - - - - - -\n\n");

    // NEW SOCKET DESCRIPTOR
    int sockDesc = socket(PF_INET, SOCK_DGRAM, 0);
    printf("> New UDP Socket\n\n");


    // ADDRESS CONFIGURATION (PEER)
    struct sockaddr_in peerAddr;
    int peerAddrLen = sizeof(peerAddr);
    peerAddr.sin_family = AF_INET;
    peerAddr.sin_port = htons(RECEIVER_PORT);
    peerAddr.sin_addr.s_addr = inet_addr(RECEIVER_IP);
    printf("> Peer Address Configured\n\n");


    // WAIT FOR A DATAGRAM...
    printf("> Sending to %s:%d\n\n", RECEIVER_IP, RECEIVER_PORT);
    char buf[BUFLEN] = "Hello World!"; // 12 bytes
    sendto(sockDesc, buf, BUFLEN, 0, (struct sockaddr*) &peerAddr, peerAddrLen);
    printf("> Sent.\n\n");
    

    // CLOSE
    close(sockDesc);
    printf("> Closed\n\n");

    printf("- - - - - - - - - - - - - - - - - -\n");
    return 0;

}

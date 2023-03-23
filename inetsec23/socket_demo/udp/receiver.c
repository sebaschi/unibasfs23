// udp/receiver.c

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define   RECEIVER_PORT   8888
#define   BUFLEN          12

/*** UDP RECEIVER ***/
int main() {

    printf("- - - - - - - - - - - - - - - - - -\n\n");

    // NEW SOCKET DESCRIPTOR
    int sockDesc = socket(PF_INET, SOCK_DGRAM, 0);
    printf("> New UDP Socket\n\n");


    // ADDRESS CONFIGURATION (LOCAL)
    struct sockaddr_in locAddr;
    locAddr.sin_family = AF_INET;
    locAddr.sin_port = htons(RECEIVER_PORT);
    locAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("> Local Address Configured\n\n");


    // ADDRESS CONFIGURATION (PEER)
    struct sockaddr_in peerAddr;
    socklen_t peerAddrLen = sizeof(peerAddr);
    printf("> Peer Address Allocated\n\n");


    // BINDING
    bind(sockDesc, (struct sockaddr*) &locAddr, sizeof(locAddr));
    printf("> Bound to port %d\n\n", RECEIVER_PORT);


    // WAIT FOR A DATAGRAM...
    printf("> Waitig for datagram...\n\n");
    char buf[BUFLEN];
    int recvLen = recvfrom(sockDesc, buf, BUFLEN, 0, (struct sockaddr*) &peerAddr, &peerAddrLen);
    printf("> Received %d bytes from %s:%d\n\n", recvLen, 
                                             inet_ntoa(peerAddr.sin_addr),
                                             ntohs(peerAddr.sin_port) );
    printf("> Buffer contains (interpreted as string): %s \n\n", buf);
    

    // CLOSE
    //close(sockDesc);
    printf("> Closed\n\n");

    printf("- - - - - - - - - - - - - - - - - -\n");
    return 0;

}

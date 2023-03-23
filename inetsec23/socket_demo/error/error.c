#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// NOTE: ONLY PRIVILEDGED USERS CAN BIND ON PORTS BELOW 1024 !!!

#define    PORT    80

int main() {

    // -- NEW SOCKET DESCRIPTOR
    int sockDesc = socket(PF_INET, SOCK_DGRAM, 0);
    if ( sockDesc < 0 ) {
        perror("socket: " );
        return -1;
    }
    printf("> New UDP Socket\n");


    // -- ADDRESS CONFIGURATION (LOCAL)
    struct sockaddr_in locAddr;
    locAddr.sin_family = AF_INET;
    locAddr.sin_port = htons(PORT);
    locAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // -- BINDING
    if ( bind(sockDesc, (struct sockaddr*) &locAddr, sizeof(locAddr)) < 0 ) {
        perror("bind: ");
        return -1;
    }
    printf("> Bound on port %d\n", PORT);
    
   
    // -- DO STUFF
    printf("  ... do useful stuff ...\n");

    // -- CLOSE
    close(sockDesc);
    printf("> Closed\n");

    return 0;

}

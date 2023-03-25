// tcp/chat-client.c
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define MAXPENDING 10
#define BUFSIZE 512
#define STDPORT "8080"

int server (char *, char);
void *recv_msg (void *);
void *send_msg (void *);
int client (char *, char *);
struct thread_args {
    int sock;
    int port;
};
int main (int argc, char **argv){
    // NEW SOCKET DESCRIPTOR
    int tcp_socket = socket (PF_INET, SOCK_STREAM, 0);
    printf (">New TCP socket \n\n");

    int ret;
    // Check if Arguments given at start of program
    if (argc == 1)
    {
        ret = server(STDPORT, 'd');
    }
    else if (argc == 2)
    {
        ret = server(argv[1], 'd');
    }
    else
    {
        ret = client(argv[1], argv[2]);
    }
    return 0;
}

int server (char *port, char s)
{
    int servSock = socket (PF_INET, SOCK_STREAM, 0);
    printf ("New Server TCP Socket\n\n");

    // Configure Address in "server mode"
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons (atoi (port));
    if (s == 's')
    {
        servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
    }
    else
    {
        servAddr.sin_addr.s_addr = inet_addr ("127.0.0.1");
    }
    printf ("Server Configured at IP %s\n\n", inet_ntoa (servAddr.sin_addr));

    // Bind
    bind (servSock, (struct sockaddr *)&servAddr, sizeof (servAddr));
    printf ("Socket and Address Config Bound.\n\n");

    // Listen until client arrives
    listen (servSock, MAXPENDING);
    printf ("Started Listening on Port %u\n\n", ntohs (servAddr.sin_port));

    struct sockaddr_in cltAddr;
    socklen_t cltAddrLen = sizeof (cltAddr);
    int cltSock;
    printf ("Allocated Client Address\n\n");

    cltSock = accept (servSock, (struct sockaddr *)&cltAddr, &cltAddrLen);
    printf("New client Accepted on port %u\n\n", ntohs(cltAddr.sin_port));

    //Save Client port Addr 
    unsigned short peerPort = ntohs(cltAddr.sin_port);
   

    struct thread_args in = { .sock = cltSock, .port=peerPort};
    //Create receiver thread
    pthread_t recv_thread;
    if (pthread_create(&recv_thread, NULL, recv_msg, &in) != 0) {
        perror("pthread_create(RECV) error");
        exit(1);
    }

    //Create sender thread
    pthread_t send_thread;
    if (pthread_create(&send_thread, NULL, send_msg, &in) != 0) {
        perror("pthread_create(SENDER) error");
        exit(1);
    }

    //join
    if(pthread_join(recv_thread,NULL) != 0){
        perror("pthread_join(RECV) error");
        exit(3);
    }
    if (pthread_join(send_thread,NULL) != 0){
        perror("pthread_join(SEND) error");
        exit(3);
    }

    close(cltSock);
    close(servSock);
    return 1;
}

//Client Mode
int client(char *ip, char *port){

    //New Socket
    int localSock = socket(PF_INET,SOCK_STREAM,0);
    printf("New Socket in Client Mode\n\n");

    //Local Address Config
    struct sockaddr_in localAddr;
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(0);
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    printf ("Local Address Configured at IP %s, port %u\n\n", inet_ntoa (localAddr.sin_addr), ntohs(localAddr.sin_port));
    
    //Bind
    bind(localSock, (struct sockaddr*) &localAddr, sizeof(localAddr));
    printf("Bound Socket in Client mode\n\n");


    //Configure Remote
    struct sockaddr_in srvAddr;
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(atoi(port));
    srvAddr.sin_addr.s_addr = inet_addr(ip);
    printf("Remote Configured at ip %s port %s\n\n",ip,port);

    //Connect to remote
    connect(localSock, (struct sockaddr*) &srvAddr, sizeof(srvAddr));
    printf("Connected to remote\n\n");
    
    struct thread_args in = {.sock = localSock, .port=atoi(port)};
    //Create receiver thread
    pthread_t recv_thread;
    if (pthread_create(&recv_thread, NULL, recv_msg, &in) != 0) {
        perror("pthread_create(RECV) error");
        exit(1);
    }

    //Create sender thread
    pthread_t send_thread;
    if (pthread_create(&send_thread, NULL, send_msg, &in) != 0) {
        perror("pthread_create(SENDER) error");
        exit(1);
    }

    //join
    if(pthread_join(recv_thread,NULL) != 0){
        perror("pthread_join(RECV) error");
        exit(3);
    }
    if (pthread_join(send_thread,NULL) != 0){
        perror("pthread_join(SEND) error");
        exit(3);
    }

    close(localSock);
    return 0;

}




//Receive Mesage Function
void *recv_msg (void *args_void)
{
    struct thread_args *args = args_void;
    char *buf = malloc(sizeof(char) * BUFSIZE);
    int bytesRecv;
    int cltSock = args->sock;
    int port = args->port;
    memset(buf,0,BUFSIZE);
    do
    {
        
        memset(buf,0,BUFSIZE);
        bytesRecv = recv (cltSock,buf, BUFSIZE, 0);
        if (bytesRecv == 0){pthread_exit(NULL);}
        char msgRecv[bytesRecv];
        strncpy (msgRecv, buf, bytesRecv+1);
        printf ("%d> %s", port, msgRecv);
        memset(buf,0,BUFSIZE);
    }
    while (bytesRecv != -1);
    free(buf);
    pthread_exit(NULL);
}

//Send Message function
void *send_msg (void *args_void)
{
    sleep(1);
    struct thread_args *args = args_void;
    char *buf = malloc(sizeof(char) * BUFSIZE);
    int ret;
    int socket = args->sock;
    int i = 0;
    memset(buf,0,BUFSIZE);
    while ((ret = read(0,buf,BUFSIZE)!=-1)) {
        
        send(socket, buf, strlen(buf), 0);
        memset(buf,0,BUFSIZE);
    }
    free(buf);
    pthread_exit(NULL);
}


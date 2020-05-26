#include "net_utils.h"
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv){
    if(argc < 3){
        printf("usage: ./timestampTcpClient server_ip name\n");
        exit(EXIT_SUCCESS);
    }
    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9999); // pay attention
    Inet_aton(argv[1], &servaddr.sin_addr);

    Connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));
    
    int size;
    
    if((size = send(sockfd, argv[2], strlen(argv[2]), 0)) < strlen(argv[2])){
        perror("send");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    char recvbuf[2048];
    bzero(recvbuf, 2048);
    if((size = recv(sockfd, recvbuf, 2048, 0)) <= 0){
        perror("recv");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("%s\n", recvbuf);
    return 0;
}
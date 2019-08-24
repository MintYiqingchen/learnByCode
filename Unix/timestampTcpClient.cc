#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
int Socket(int domain, int sockettype, int protocol){
    int fd;
    if((fd=socket(domain, sockettype, protocol)) < 0){
        perror("socket");
        exit(-1);
    }
    return fd;
}

void Inet_aton(char* ip_str, in_addr* addr){
    if(inet_aton(ip_str, addr) == 0){
        perror("inet_aton");
        exit(-1);
    }
}

void Bind(int fd, const sockaddr* addr, socklen_t len){
    if(bind(fd, addr, len) < 0){
        perror("bind");
        exit(-1);
    }
}

void Connect(int fd, sockaddr* addr, socklen_t size){
    if(connect(fd, addr, size) < 0){
        perror("connect");
        exit(-1);
    }
}
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
    
    char recvbuf[1024];
    if((size = recv(sockfd, recvbuf, 1024, 0)) <= 0){
        perror("recv");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("%s\n", recvbuf);
    return 0;
}
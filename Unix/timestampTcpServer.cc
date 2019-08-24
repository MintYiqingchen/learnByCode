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

void Listen(int fd, int backlog){
    if(listen(fd, backlog) < -1){
        perror("listen");
        exit(-1);
    }
}

size_t get_current_time(char* buf, size_t size){
    time_t t = time(NULL);
    tm *tmp;
    tmp = localtime(&t);
    if (tmp == NULL) {
        perror("localtime");
        return 0;
    }

    
    if ((size=strftime(buf, size, "%F %T", tmp)) == 0) {
        perror("strftime");
        return 0;
    }
    return size;
}
int main(int argc, char** argv){
    if(argc < 2){
        printf("usage: ./timestampTcpServer 0.0.0.0\n");
        exit(EXIT_SUCCESS);
    }
    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in myaddr, peeraddr;
    bzero(&myaddr, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(9999); // pay attention
    Inet_aton(argv[1], &myaddr.sin_addr);
    Bind(sockfd, (sockaddr*)&myaddr, sizeof(myaddr));
    Listen(sockfd, 128); // backlog mean ?

    while(1){
        int size = sizeof(peeraddr);
        int peerfd = accept(sockfd, (sockaddr*)&peeraddr, (socklen_t*)&size);

        if(peerfd < 0){
            perror("accept");
            continue;
        }
        
        char name[256];
        bzero(name, 256);
        if((size=recv(peerfd, name, 256, 0)) < 0){
            perror("recv");
            close(peerfd);
            continue;
        }
        char msgdata[1024];
        bzero(msgdata, 1024);
        snprintf(msgdata, 1024, "hello, %s, now time is ", name);
        get_current_time(msgdata + strlen(msgdata), 1024 - strlen(msgdata));
        
        if((size = send(peerfd, msgdata, strlen(msgdata), 0)) < 0){
            perror("send");
        }
        close(peerfd);

    }
}
#include "net_utils.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


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
        int pid ;
        if((pid = fork()) == 0){
            close(sockfd);

            char name[256];
            bzero(name, 256);
            if((size=recv(peerfd, name, 256, 0)) < 0){
                perror("recv");
                close(peerfd);
                continue;
            }
            char msgdata[2048];
            bzero(msgdata, 2048);
            snprintf(msgdata, 2048, "Process %d: hello, %s, now time is ", (int)getpid(), name);
            get_current_time(msgdata + strlen(msgdata), 2048 - strlen(msgdata));
            
            if((size = send(peerfd, msgdata, strlen(msgdata), 0)) < 0){
                perror("send");
            }
            close(peerfd);
            return 0;
        }
        
        close(peerfd);
    }
}
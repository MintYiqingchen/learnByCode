#include "net_utils.h"
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

void Connect(int fd, sockaddr* addr, socklen_t size, int retry){
    do{
        if(connect(fd, addr, size) < 0){
            if(errno == ECONNREFUSED && retry > 1){
                sleep(2);
                continue;
            }
            perror("connect");
            exit(-1);
        } 
        break;
    } while(--retry);
    
}

void Listen(int fd, int backlog){
    if(listen(fd, backlog) < -1){
        perror("listen");
        exit(-1);
    }
}
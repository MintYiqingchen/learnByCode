#ifndef __NET_UTILS_H__
#define __NET_UTILS_H__
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/errno.h>

int Socket(int domain, int sockettype, int protocol);

void Inet_aton(char* ip_str, in_addr* addr);

void Bind(int fd, const sockaddr* addr, socklen_t len);

void Connect(int fd, sockaddr* addr, socklen_t size, int retry = 5);

void Listen(int fd, int backlog);

#endif
# coding:utf8

from socket import *

serverSocket=socket(AF_INET,SOCK_DGRAM)
serverSocket.bind(('',1900))
print('Server is ready to receive')
while(True):
	mes,adr=serverSocket.recvfrom(1024)
	mes=mes.upper()
	serverSocket.sendto(mes,adr)


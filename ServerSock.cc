#include "Socket.h"

ServerListenSocket::ServerListenSocket(fstream &conf):BasicSocket(conf)
{
	//use api to find the server's ip itself
	//use conf to set the port and the sock type itself 
	//BasicSocket(fstream conf);	
}

bool ServerListenSocket::BindIpAddrAndPort()
{
	//listen()
}

void ServerListenSocket::ListenClientApplication(int listen_array_length)
{
	//sock_fd sockId = this->sockId;
	listen(this->sockId, listen_array_length);
}

sock_fd ServerListenSocket::AcceptClientSocket()
{
	socklen_t sockAddrLen = sizeof(this->sockAddr);
	sock_fd clientSockId = accept(this->sockId, (struct sockaddr*)(&(this->sockAddr)), &sockAddrLen);
	return clientSockId;
}

ServerOperateSocket::ServerOperateSocket(int sock_fd, struct sockaddr_in sock_addr)
{	
	this->sockId = sock_fd;
	this->sockAddr = sock_addr;
}

sock_fd BasicSocket::GetSockId() const
{
	return this->sockId;
}

struct sockaddr_in BasicSocket::GetSockAddr() const
{
	return this->sockAddr;
}

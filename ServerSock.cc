#include "Socket.h"

ServerListenSocket::ServerListenSocket(fstream conf)
{
	//use api to find the server's ip itself
	//use conf to set the port and the sock type itself 
	BasicSocket(fstream conf);
	
}

bool ServerListenSocket::BindIpAndPort()
{
	//listen()
}

void ServerListenSocet::ListenClientApplication(int listen_array_length)
{
	listen(this->sockId, listen_array_length);

}

sock_fd AcceptCLientSocket()
{

	sock_fd clientSockId = accpet(this->sockId, (struct sockaddr*)(this->clientSockAddr), sizeof(clientSock));
	return clientSockId;
}

ServerOperateSocket::ServerOperateSocket(int sock_fd, struct sockaddr_in sock_addr)
{
	//BasicSocet(sock_fd, sock_addr);	
	this->sockId = sock_id;
	this->sockAddr = sock_addr;
}

sock_fd BasicSocket::GetSockId() const
{
	return this->sockId;
}

sock_addr BasicSocket::GetSockAddr() const
{
	return this->sockAddr;
}

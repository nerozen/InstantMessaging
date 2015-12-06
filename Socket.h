#ifndef IMSOCKET_H
#define IMSOCKET_H

//for the network api
#include <wait.h>
#include <unistd.h>
#include <sys/type.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <ctime>
#include <arpa/inet>

//for the basic operation api
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctype>

#define VALVE_OF_SOCKIO_BUFFER 1024

#define SOCKMODE_TCP 1
#define SOCKMODE_UDP 2

#define SOCK_CONFIGURE_TAG_IP 1
#define SOCK_CONFIGURE_TAG_PORT 2
#define SOCK_CONFIGURE_TAG_SOCKTYPE 3

using namespace std;

typedef int sock_fd;

typedef struct 
{
	int bufferSize;
	char *buffer;
}IOBuffer;

class BasicSocket
{
	public:
		BasicSocket(file *sock_conf);//listen socket or client socket will use
		//BasicSocket(sock_fd sock_id, struct sockaddr_in sock_addr_data);//service socket use
		BasicSocket(fstream sock_conf);//in c++ style
		~BasicSocket();
		//bool InitSock()
		sock_fd GetSockId() const;
		sock_addr GetSockAddr() const;
		String RecvFromSock();
		bool SendBySock(string message_to_send);
		//bool ReInitSock(sock_fd sock_id, struct sockaddr_in sock_addr_data);
		bool CloseSocket();
	protected:
		struct sockaddr_in sockAddr;
		sock_fd sockId;
		IOBuffer sockInputBuff;
		
	private:
		int sockMode;
		bool IsDefaultSockMode() const;
		int IdentifySOckMode(string configure_content) const;
		
};

class ClientSocket : protected BasicSocket
{
	public
		ClientSocket(file *sock_conf);
		ClientSocket(fstream sock_conf);
		bool Connect();//after the construction, use the socket info to make the connection, client will use
			
};

class ServerOperateSocket : protected BasicSocket
{
	public:
		ServerOperateSocket(sock_fd sock_id, struct sockaddr_in sock_addr_data);//for the service socket,when a sevice sub process has been inited, it needs a new socket, the main processcreated the socket and then send the sockfd and the address_info to the sub process with the tube
	private:
		struct sockaddr_in clientSockAddr;
};

class ServerListenSocket : protected BasicSocket
{
	public:
		bool BindIpAddrAndPort();
		void ListenClientApplication(int listen_array_length);
		void AcceptClientSocket();
};

#endif

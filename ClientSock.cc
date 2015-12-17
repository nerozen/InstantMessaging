#include "Socket.h"

ClientSocket::ClientSocket(fstream &sock_conf):BasicSocket(sock_conf)
{		
	if(this->Connect() == false)
	{
		cout<<"client socket failed!"<<endl;
	}
}

bool ClientSocket::Connect()
{	
	if(connect(this->sockId, (struct sockaddr*)(&this->sockAddr), sizeof(this->sockAddr)) == -1)
	{
		cout<<"client connection failed!"<<endl;	
		//to redeem ,if fail still, return false
		return false;
	}
	else
	{
		return true;
	}
}

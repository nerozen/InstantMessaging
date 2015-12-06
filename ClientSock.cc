#include "Socket.h"

ClinetSocket::ClientSocket(fstream sock_conf)
{
	BasicSocket(sock_conf);//不知道能不能直接调用父类的构造函数
		
	if(this->Connect() == false)
	{
		cout<<"client socket failed!"<<endl
	}
}

bool ClientSocket::Connect()
{	
	if(connect(this->sockId, (struct sockaddr*)(this->sockAddr), strlen(this->sockAddr)) == -1)
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

#include "Socket.h"

BasicSocket::BasicSocket(fstream sock_conf)
{
	this->sockMode = -1;
	if(!sock_conf)
	{
		//exception
	}
	else
	{
		char inputLine[1024];
		//string originalConfigure;
		//string configureTag;
		//string configureContent;
		while(sock_conf.getline(inputLine, sizeof(inputLine)))
		{
			string originalConfigure(inputLine);
			int borderIndex = originalConfigure.index('=', 1);
			int contentLength = originalConfigure.size() - (borderIndex + 1);
			string configureTag = originalConfigure.substring(0, (borderIndex+1));
			string configureContent = originalConfigure.substring(borderIndex, length);

			cout<< configureTag.c_str() <<endl;
			cout<< configureContent.c_str() <<endl;

			this->SetCongfigure(configrueTag, configureContent);
		}	
	}
	if(!(this->sockId = socket(AF_INET, SOCK_STREAM, 0)))//根据UDP选项和TCP选项有不同的创建方法，这个创建socket的分支后面要重写
	{
		cout<<"basic socket init failed!"<<endl;
	}
}

void BasicSocket::SetConfigure(string congfiugre_tag, string configure_content)
{
	int tagType = IdentifyTagType(configure_tag)
	{
		switch(tagType)
		{
		case SOCK_CONFIGURE_TAG_IP:
			this->sockAddr.sin_addr.s_addr = inet_addr(configure_content.c_str());
			break;
		case SOCK_CONFIGURE_TAG_PORT:
			int port = atoi(configure_content.c_str());
			this->sock.sin_port = hton(port);
			break;
		case SOCK_CONFIGURE_TAG_SOCKTYPE: //UDP OR TCP
			//
			this->sockMode = IdentifySockMode(configure_content);
			if(this->sockMode < 0)
			{
				cout<< "mode setting failed!" <<endl;
			}
			break;
		default:
			//exception
			break;
		}
	}
}

void BasicSocket::SwitchToStandardTag(string &configure_tag)
{
	for(int index = 0; index < configure_tag.size(); index++)
	{
		configure_tag[index] = toupper(configure_tag[index]);		
	}
}

int BasicSocket::IdentifyTagType(string configure_tag)
{
	int tagType = 0;
	SwitchToStandardTag(configure_tag)
	if(configure_tag == "IP")
	{
		tagType = SOCK_CONFIGURE_TAG_IP;
		return tagType;
	}
	if(configure_tag == "PORT")
	{
		tagType = SOCK_CONFIGURE_TAG_PORT;
		return tagType;
	}
	if(configure_tag == "SOCKMODE")
	{
		tagType = SOCK_CONFIGURE_TAG_SOCKTYPE;
		return tagType;
	}
	//....
	return tagTYpe;
}


int BasicSocket::IdentifySockMode(string configure_content) const
{
	int sockMode;
	if(strcmp(configure_content.c_str(), "TCP") == 0)
	{
		sockMode = SOCKMODE_TCP;	
	}
	else if(strcmp(configure_content.c_str(), "UDP") == 0)
		{
			sockMode = SOCKMODE_UDP;
		}
		else
		{
			sockMode = -1;
		}
	return sockMode;	
}

int BasicSocket::SendBySock(string message_to_send)
{
	char *messageToSend = message_to_send.c_str();
	int bufferSize = strlen(messageToSend);
	int sendBiteAmount;
	sendBiteAmount = send(this->sockid, messagetosend, bufferSize, 0);
	return ssendBiteAmount;	
}

string BasicSocket::RecvFromSock()
{
	memset(this->sockInputBuff.buffer);
	recv(this->sockId, this->sockInputBuff.buffer, this->sockInputBuff.bufferSize, 0);
	string RecivedMessage(this->sockInputBuff.buffer);
	return RecivedMessage;
}

BasicSocket::BasicSocket(file *sock_conf)//open the conf file in the C style(using file pointer)
{
	while(!eof(sock_conf))
	{
		
	}
}


bool BasicSocket::IsDefaultCommunicationMode() const
{
	return sockMode == 1 ? true : false;
}

#include "IMProtocolManager.h"

Protocol init_packed_protocol(string protocol_content)
{
	Protocol packedProtocol;
	packProtocol.packedData = protocol_content;	
}

Protocol ProtocolManager::PackageLoginData(string user_id, string encrypted_psd, int encryption_key)
{
	string protocolContent;
	PrePack(&protocolContent, user_id, PTYPE_SYSTEM_LOGIN);	
	PackEncryptionKey(&protocolContent, encryption_key);
	PackMainBody(&protocolContent, encrypted_psd);
	Protocol doneProtocol = init_packed_protocol(protocolContent);
	return PackedProtocol;	
}


int ProtocolManager::PrePack(string &protocol_content, string user_id, ProtocolType protocol_type)
{
	switch(protocol_type)
	{
		case PTYPE_SYSTEM_LOGIN:
			
			protocol_content += PackSegmentSource(user_id);
			protocol_content += PackSegmentDestination(protocolStandardRoleServer);//function could be merged
			protocol_content += PackSegment(HEAD_TAG_FUNCTION, protocolFunctionHeadTag, protocolStandardLevelSys);//function not defined
			protocol_content += PackSegment(HEAD_TAG_FOR, protocolForHeadTag, protocolStandardActivityLogin);//
			break;
		default
			//exception();
			break;
	}
	return 1;
}

int ProtocolManager::PackEncryptionKey(sting &protocol_content, string encryption_key,)
{
	protocol_content+= (protocolOptionalEKeyTag + encryption_key);
	protocol_content.push_back('\n');
	
	return 1;
}
/*
int ProtocolManager::PackPassWord(string &protocol_content, string encrypted_psd) 
{
	protocol_content+= (protocolOptionalPsdTag + encrypted_psd;
	protocol_content.push_back('\n');

	return 1;
}
*/

int ProtocolManager::PackSegementInGenel(string &protocol_content, string segement_tag, string segement_content)
{
	protocol_content += (segement_tag + segement_content)
	protocol_content.push_back('\n');
	return 1;
}

int ProtocolManager::PackMainBody(string &protocol_content, string main_body)
{
	protocol_content+= (protocolMainBody + main_body)	
	protocol_content.push_back('\n');
}

string ProtocolManager::PackSegmentSource(string source)
{
	string sendSourceHead = this->protocolSourceHead + source;  
	sendSOurceHead.push_back('\n');
	return sendSourceHead;
}

string ProtocolManager::PackSegmentDestination(string destination)
{
	string destinationHead = this->protocolDestinationHeadTag + destination;
	destinationHead.push_back('\n');
	return destinationHead;
}

string ProtocolManager::PackSegmentFor(string for_purpose)
{
	string forHead = this->protocolForHeadTag + for_purpose;
	forHead.push_back('\n');
	return forHead;
}

string ProtocolManager::PackSegmentFunction(string function)
{
	string functionHead = this->protocolForHeadTag + fucntion;
	functionHead.push_back('\n');
	return functionHead;
}

string ProtocolManager::GenearlPackSegment(HeadTagType head_tag, string tag_content)
{
	string protocolHead; 
	switch(HeadTagTYpe)
	{
		case HEAD_TAG_FROM:			
			protocolHead += (this->protocolSourceHeadTag + tag_content);
			break;
		case HEAD_TAG_TO:
			protocolHead += (this->protocolDestinationHeadTag + tag_content);
			break;
		case HEAD_TAG_FUNCTION:
			protocolHead += (this->protocolFunctionHeadTag + tag_content);
			break;
		case HEAD_TAG_FOR:			
			protocolHead += (this->protocolForHeadTag + tag_content);
			break;
		default:
			//exception;
			break; 
	}
	protocolHead.push_back('\n');
	return protocolHead;	
}

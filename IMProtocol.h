#ifndef IMPROTOCOL_H
#define IMPROTOCOL_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

#define PTYPE_SYSTEM_LOGIN 1
#define PTYPE_SYSTEM_LOGOUT 2
#define PTYPE_FUNCTION_P2PCHAT 3
#define PTYPE_FUNCTION_GPCHAT 4
#define PTYPE_FUNCTION_P2PFILE 5
#define PTYPE_FUNCTION_GPFILE 6

#define HEAD_TAG_FROM 11
#define HEAD_TAG_TO 12
#define HEAD_TAG_FUNCTION 13
#define HEAD_TAG_FOR 14

typedef int ProtocolType;
typedef int HeadTagType;

class ProtocolManager
{
	public:
		int PackageLoginData(string user_id, string encrypted_psd, int encryption_key);
		int PrePack(string &protocol_content, string user_id, ProtocolType protocol_type);
		int PackEncryptionKey(string &protocol_content, string encryption_key);
		//int PackPassWord(string &protocol_content, string encrypted_psd);
		int PackSegementInGenel(string &protocol_content, string segement_tag, string segement_content);
		int PackMainBody(string &protocol_content, string main_body);
		string PackSegementSource(string source);
		string PackSegementDestination(string destination);
		string PackSegementFunction(string function);
		string PackSegementFor(string for_purpose);
		string GeneralPackSegement(HeadTagTYpe head_tag, string tag_content);
		
	private:
		//static const string protocolOptionalPsdTag = "PASSWORD:";
		static const string protocolOptionalEKeyTag = "KEY:";
		static const string protocolSourceHeadTag = "FROM:";
		static const string protocolDestinationHeadTag = "TO:";
		static const string protocolFunctionHeadTag = "FUNCTION:";
		static const string protocolForHeadTag = "FOR";
		static const string protocolStandardLevelSys = "SYSTEM";
		static const string protocolStandardRoleServer = "SERVER";
		static const string protocolStandardActivity = "LOGIN";
};

Protocol init_packed_protocol(string protocol_content);

typedef struct strc_protocol
{
	string packagedData;
}Protocol;
#endif 

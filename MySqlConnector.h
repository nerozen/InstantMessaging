#ifndef MYSQLCONNECTOR_H
#define MYSQLCONNECTOR_H

#include <iostream>
#include <cstdio>
#include <string>
#include <mysql.h>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <map>

#define QUERY_TYPE_INSERT 1
#define QUERY_TYPE_UPDATE 2
#define QUERY_TYPE_DELETE 3
#define QUERY_TYPE_SELECT 4
#define QUERY_TYPE_DBADMIN_CHUSR 5
#define QUERY_TYPE_DBADMIN_CHDB 6

#define ADMIN_CHANGE_HOST 1
#define ADMIN_CHANGE_PORT 2
#define ADMIN_CHANGE_USER 3
#define ADMIN_CHANGE_PSWD 4
#define ADMIN_CHANGE_DBNM 5

static const char *global_default_HostName = "localhost";
static const char *global_default_UsrName = "root";
static const char *global_default_Password = "root";
static const char *global_default_DBName = "LC_instant_messaging";
static const int global_default_port = 3307;

using namespace std;

typedef int QType;

class MySqlConnector
{
	public:
		MySqlConnector();//to open configfile to init the initial dbconnection
		//MySqlConnector(vector<string> connection_arguments);
		MySqlConnector(FILE *config_file_ptr);
		void DecodeConfigure(string undecode_configure);
		void InitMySqlConnectCommand();
		char *GetCurrentHostName() const;
		char *GetCurrentUserName() const;		
		char *GetCurrentDBName() const;
		int GetCurrentPort() const;
		//char **GetModifyGeneralInfo(vector<int> option_vec) const;
		bool IsInUsing() const;
		int GeneralSqlQuery(string sql_query, QType query_type);
		string SelectCommand(string sql_query);
		int UpdateCommand(string sql_query);
		bool InsertCommand(string sql_query);
		int DeleteCommand(string sql_query);
		//adminstration modify
		bool AdminChange(map<int string> option_map);
		//bool AdminChange(vector<string> option_array);
		bool ChangeUsrOrDb(string user_name, string password, string db_name);
		void CloseConnection();	
		
		//~MySqlConnector();
	
	private:
		MYSQL connectorCore;
		char *hostName;
		char *userName;
		char *passWord;
		char *DBName;
		int port;
		int SetUsingStatus();
		bool isAble;//for the thread sqqurity
		bool isInUsing;//for the thread sequrity
		bool IsConnectorAble() const;
		void EnableConnector();
		void UnableConnector();
		void SetHostName(string host_name_to_set);
		void SetUserName(string username_to_set);
		void SetPassWord(string password_to_set);
		void SetDataBase(string dbname_to_set);
		bool IsChangeLeagel();
		void RollBackToFormerConnection();
		int SetConnectorAtributions(vector<int> atributions_tag_vec, vector<string> atributions_vec);
		int SetSingleConnectorArtibution(int atribution_tag, string artibution_to_change);
		void unDecodeConfigure(string undecode_configure);
};

typedef struct
{
	string fileName;
	FILE *filePtr;
	
}FileData;

FileData *read_file(string file_path, string open_option);
bool is_leagel_open_option(string open_option);

#endif

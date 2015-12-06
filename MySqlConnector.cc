#include "MySqlConnector.h"

FileData *read_file(string file_path, string open_option)
{
	FileData *fDPtr = NULL;
	FILE *fPtr = NULL;
	if(is_leagel_open_option(open_option))
	{	
		 fPtr = fopen(file_path.c_str(), open_option.c_str());
	}
	else
	{
		//excepiton
		//return (FileData*)(&0);
	}
	
	if(fPtr)
	{
		fDPtr = new FileData;
		fDPtr-> fileName = file_path;
		fDPtr->filePtr = fPtr;	
	}
	else
	{
		//exception
	}
	return fDPtr;
}

bool is_leagel_open_option(string open_option)
{
	//return open_option == 'r'||open_option == 'w';
	
	return true;
}

MySqlConnector::MySqlConnector(FILE *config_file_ptr)
{
	//ReadingConfigureFIle(config_file_ptr);
	string unDecodedSingleConfigure;
	while(!feof(config_file_ptr))
	{
		char fileChar = fgetc(config_file_ptr);
		if(fileChar == '\n')
		{
			if(unDecodedSingleConfigure.size() == 0)
			{
				continue;
			}
			DecodeConfigure(unDecodedSingleConfigure);
			unDecodedSingleConfigure.clear();
		}
		else
		{
			unDecodedSingleConfigure.push_back(fileChar);
		}
		//config_file_ptr++;
	}
/*
	if(IsAllValid())
	{

	}
*/
	if(mysql_init(&connectorCore))
	{
		cout<<"mysql init failed"<<endl;
	}
	if(mysql_real_connect(&(this->connectorCore), this->hostName, this->userName, this->passWord, this->DBName, this->port, NULL, 0) == 0)
	{
		//exception
		cout<<"mysql connection failed!"<<endl;
	}
	else
	{
		return;
	}
	mysql_query(&connectorCore, "set names utf-8");
}

void MySqlConnector::DecodeConfigure(string undecode_configure)
{
	string configureTag;
	string configureContent;
	for(int index = 0; index < undecode_configure.size(); index++)
	{
		if(undecode_configure[index] == '=')
		{
			configureTag = undecode_configure.substr(0, index - 1);
			configureContent = undecode_configure.substr(index + 1, undecode_configure.size()-1);
			//break;
			
			if(configureTag == "HOSTNAME")
			{
				this->hostName = new char[configureContent.size()];
				strcpy(this->hostName, configureContent.c_str());
				configureTag.clear();
				configureContent.clear();
				break;
			}
			if(configureTag == "USERNAME")
			{
				this->userName = new char[configureContent.size()];
				strcpy(this->userName, configureContent.c_str());
				configureTag.clear();
				configureContent.clear();
				break;
			}
			if(configureTag == "PASSWORD")
			{
				this->passWord = new char[configureContent.size()];
				strcpy(this->passWord, configureContent.c_str());
				configureTag.clear();
				configureContent.clear();
				break;
			}
			if(configureTag == "DBNAME")
			{
				this->DBName = new char[configureContent.size()];
				strcpy(this->DBName, configureContent.c_str());
				configureTag.clear();
				configureContent.clear();
				break;
			}
			if(configureTag == "PORT")
			{
				this->port = atoi(configureContent.c_str());
				configureTag.clear();
				configureContent.clear();
			}	
		}
	}
}
	
MySqlConnector::MySqlConnector()
{
	//MYSQL haha;
	//cout<<"haha"<<endl;
	mysql_init(&connectorCore);
	hostName = new char[strlen(global_default_HostName)];
	userName = new char[strlen(global_default_UsrName)];
	passWord = new char[strlen(global_default_Password)];
	DBName = new char[strlen(global_default_DBName)];
	strcpy(hostName, global_default_HostName);
	strcpy(userName, global_default_UsrName);
	strcpy(passWord, global_default_Password);
	strcpy(DBName, global_default_DBName);
	port = global_default_port;

	if (&connectorCore == NULL)
	{
		cout << "initialization error" << endl;
		system("pause");
		exit(0);
	}
	
	if(mysql_real_connect(&(this->connectorCore), this->hostName, this->userName, this->passWord, this->DBName, this->port, NULL, 0) == 0)
	{
		//exception
		cout<<"mysql connection failed!"<<endl;
	}
	else
	{
		return;
	}
	mysql_query(&connectorCore, "set names utf-8");
}

void MySqlConnector::InitMySqlConnectCommand()
{
	mysql_real_connect(&connectorCore, global_default_HostName, global_default_UsrName, global_default_Password, global_default_DBName, global_default_port, NULL, 0);
	if (&connectorCore == NULL)
	{
		cout << "connection error"<<endl;
		system("pasue");
	}
	mysql_query(&connectorCore, "set names utf8");
}

bool MySqlConnector::ChangeUsrOrDb(string user_name, string password, string db_name)
{
	const char *dbNameToChange = db_name.c_str();
	if (user_name == "")
	{
		
		//const char *passWordToChange = passWord;
		//mysql_change_user(&connectorCore, this->userName, this->passWord, dbNameToChange);
		if(mysql_select_db(&connectorCore, dbNameToChange))
		{
			//fail!	
		}
		else
		{
			//success
		}
	}
	else
	{
		//const char *dbName
		const char *passWordToChange = password.c_str();
		const char *userNameToChange = user_name.c_str();
		if (db_name == "")
		{
			mysql_change_user(&connectorCore, userNameToChange, passWordToChange, this->DBName);
		}
		else
		{
			mysql_change_user(&connectorCore, userNameToChange, passWordToChange, dbNameToChange);
		}
	}
}

string MySqlConnector::SelectCommand(string SqlSelectQuery)
{
	MYSQL_RES *ResultSetsPtr;
	MYSQL_ROW SingleRecord;

	string ResultSetsInString;

	//mysql_query(connectorCore, "set character_set_results='utf8'"); Éè¶¨·µ»ØµÄ½á¹û¼¯µÄ×Ö·û¼¯Îªutf8£¬µ«ÊÇÇ°Ãæ³õÊ¼»¯¾ÍÒÑ¾­Ö¸¶¨×Ö·û¼¯ÁË£¬¸öÈËÈÏÎª´Ë´¦²»ÐèÒªÔÙ´ÎÉùÃ÷

	const char *SqlQueryAsArgument = SqlSelectQuery.c_str();

	if (mysql_real_query(&connectorCore, SqlQueryAsArgument, strlen(SqlQueryAsArgument)) == 0)
	{
		//·µ»Ø0£¬²éÑ¯³É¹¦£¬½øÐÐÏÂÒ»²½Êý¾Ý×ª»¯
		ResultSetsPtr = mysql_store_result(&connectorCore);//ÌáÈ¡½á¹û¼¯µ½½á¹¹ÌåÖÐ£¬´ËÊ±½á¹û¼¯»¹´æ´¢ÔÚ½á¹û¼¯ÖÐ£¬ÐèÒª½øÒ»²½½âÎö

		if (ResultSetsPtr != NULL)
		{
			//½á¹û¼¯²»Îª¿Õ
			int columnAmount = mysql_num_fields(ResultSetsPtr);
			while ((SingleRecord = mysql_fetch_row(ResultSetsPtr)) != NULL)
			{
				//Ã¿´Î´Ó´æ·Å½á¹û¼¯½á¹¹ÌåÖÐÌáÈ¡Ò»ÐÐ£¬¸³Öµ¸ø×Ö·û´®Êý×é			
				for (int columnIndex = 0; columnIndex < columnAmount; columnIndex++)
				{
					string SingleColumn = SingleRecord[columnIndex];
					//ÕâÀïÔ­°æÊ¹ÓÃÁËUTF82ANSIº¯Êý£¬ÕâÀïÏÈ²»µ÷ÓÃ£¬¿´¿´ÓÐÊ²Ã´Çø±ð
					ResultSetsInString += SingleColumn;
					ResultSetsInString.push_back('\t');//Ò»ÁÐ½áÊø£¬¼ÓÈëÒ»¸ö¼ä¸ô·ûºÅ£¬ÔõÃ´Ñ¡È¡¶¼ÐÐ£¬ÕâÀïÑ¡ÓÃËõ½ø·û×÷ÎªÁÐÓëÁÐµÄ¼ä¸ô
				}
				ResultSetsInString.push_back('\n');//Ã¿ÐÐÌáÈ¡ºó£¬¼ÓÉÏÒ»¸ö»»ÐÐ·û
			}
			//ResultSetsInString.push_back('\0');//È«²¿ÌáÈ¡ºó£¬¼ÓÉÏÖÕ½á·û		
		}
		else
		{
			//½á¹û¼¯Îª¿Õ
			cout << "Óï¾äÖ´ÐÐ³É¹¦£¬µ«½á¹û¼¯Îª¿Õ"<<mysql_error(&connectorCore)<< endl;
			//cout << mysql_errno(&connectorCore);		
			system("pause");
		}
	}
	else
	{
		//·µ»Ø·ÇÁã£¬²éÑ¯Ê§°Ü£¬²éÃ÷Ô­Òò
		string errorMessage = mysql_error(&connectorCore);
		cout << "there is an error while a select command running " + errorMessage << endl;	
		system("pause");
	}
	return ResultSetsInString;
}

int MySqlConnector::DeleteCommand(string sql_delete_query)
{
	int affectedRowNums = -1;
	const char* sqlDeleteAsArguement = sql_delete_query.c_str();

	if (!mysql_real_query(&connectorCore, sqlDeleteAsArguement, strlen(sqlDeleteAsArguement)))
	{
		cout << "delete successfully!" << endl;
		affectedRowNums = mysql_affected_rows(&connectorCore);
	}
	else
	{
		string errorMessage = mysql_error(&connectorCore);
		cout << "delete failed! " << endl;
		cout << errorMessage<<endl;
	}
	return affectedRowNums;
}

bool MySqlConnector::InsertCommand(string sql_insert_query)
{
	bool isSuccessed = false;
	const char* sqlInsertAsarguement = sql_insert_query.c_str();

	if (!mysql_real_query(&connectorCore, sqlInsertAsarguement, strlen(sqlInsertAsarguement)))
	{
		isSuccessed = true;
	}
	else
	{
		string erroeMessage = mysql_error(&connectorCore);
	}
	return isSuccessed;
}

int MySqlConnector::UpdateCommand(string sql_update_query)
{
	int affectedRowNums = -1;
	const char* sqlUpdateAsArguement = sql_update_query.c_str();

	if (!mysql_real_query(&connectorCore, sqlUpdateAsArguement, strlen(sqlUpdateAsArguement)))
	{
		cout << "delete successfully!" << endl;
		affectedRowNums = mysql_affected_rows(&connectorCore);
	}
	else
	{
		string errorMessage = mysql_error(&connectorCore);
		cout << "update failed! " << endl;
		cout << errorMessage << endl;
	}
	return affectedRowNums;
}

void MySqlConnector::CloseConnection()
{
	mysql_close(&connectorCore);
}

char* MySqlConnector::GetCurrentHostName () const
{
	return hostName;
}

char* MySqlConnector::GetCurrentUserName() const
{
	return userName;
}

char* MySqlConnector::GetCurrentDBName() const
{
	return DBName;
}

int MySqlConnector::GetCurrentPort() const
{
	return port;
}

bool MySqlConnector::AdminChange(map<int string> connector_arguments_to_change)
{
	//
	UnableConnector();
	bool isSuccessed = true;
	map<int string>::iterator connArgueArrayItrer;
	char *tempHostName = this->hostName;
	char *tempUserName = this->userName;
	char *tempPassWord = this->PassWord;
	char *tempDBName = this->DBName;
	int tempPort = this->port;
	
	connArgueArrayItrer = connector_arguments_to_change.find(ADMIN_CHANGE_HOST);
	
	for(; connArgueArrayIter != connector_arguments_to_change.end(); connArgueArrayIter++)
	{
		int arguementTag = connArgueArrayIter->first;
		string singleArguement = connArgueArrayIter->second;
		//
		SetSingleConnectorArtibution(arguementTag, singleArguement);
	}
	if(IsChangeLeagel())
	{
		
	}
	else
	{
		RollBackToFormerConnection();	
		isSuccessed = false;
	}
	EnableConnector();
	return isSuccessed;
}

void MySqlConnector::SetSingleConnectorArtibution(int atribution_tag, string atribution_to_change)
{
	switch(atribution_tag)
	{
	case ADMIN_CHANGE_HOST:
		SetHostName(atribution_to_change);
		break;
	case ADMIN_CHANGE_PORT:
		SetUserName(atribution_to_change);
		break;
	case ADMIN_CHANGE_USER:
		SetPassWord(atribuiton_to_change);
		break;
	case ADMIN_CHANGE_PSWD:
		SetUserName(atribution_to_change);
		break;
	case ADMIN_CHANGE_DBNM:
		SetDataBase(atribution_to_change);
		break;
	default:
		//exception
		break;
	}
}

bool IsChangeLeagel()
{
	bool isLeagel = true;
	
	mysql_init(&connectorCore);
	mysql_real_connect();

	return isLeagel;	
}

bool MySqlConnector::AdminChange(map<int string>::iterator connector_arguments_to_change)
{}

void MySqlConnector::SetHostName(string host_name_to_set)
{
	this->isAble = false;
	const char* hostNameToSet = host_name_to_set.c_str();
	free(hostName);
	hostName = new char[strlen(hostNameToSet)];
	strcpy(hostName, hostNameToSet);
}

void MySqlConnector::SetUserName(string username_to_set)
{
	this->isAble = false;
	const char* userNameToSet = username_to_set.c_str();
	free(userName);
	userName = new char[strlen(userNameToSet)];
	strcpy(userName, userNameToSet);
}

void MySqlConnector::SetPassWord(string password_to_set)
{}

void MySqlConnector::SetDataBase(string dbname_to_set)
{}

void RollBackToFormerConnection()
{}

void MySqlConnector::SetConnectorAtributions(vector<int> atributions_tag_vec, vector<string> atributions_vec)
{}

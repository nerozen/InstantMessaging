#include <stdio.h>
#include <string.h>
#include "mysql.h"


const char* global_HostName = "localhost";
const char* global_UsrName = "root";
const char* global_Password = "199694";
const char* global_DBName = "test";
int global_port = 18184;

int createConnector(MYSQL ConnectorCore) {
	mysql_init(&ConnectorCore);
	
	if (&ConnectorCore == NULL)
	{
		printf("error----------create");
		return 0;
	}
	else
		return 1;
}
int initConnector(MYSQL ConnectorCore)
{
	mysql_real_connect(&ConnectorCore, global_HostName, global_UsrName, global_Password, global_DBName, global_port, NULL, 0);
	if (&ConnectorCore == NULL)
	{
		printf("error--------------init");
		return 0;
	}
	else
		return 1;
}
int isExist(char *number, char *password_real, MYSQL ConnectorCore)
{
	MYSQL_RES *result_setsPtr;
	char command [53] = "SELECT password FROM TABLE user WHERE number = ";
	strcat(command,number);
	MYSQL_ROW row;	

	mysql_real_query(&ConnectorCore, command, strlen(command))	;

	if ( mysql_real_query(&ConnectorCore, command, strlen(command) ) == 0){
		if ( (result_setsPtr = mysql_store_result (&ConnectorCore)) !=NULL )
		{
				row = mysql_fetch_row(result_setsPtr);
				password_real = *row;				
				return 1;
		}	
		else 
			{
				printf("出错！");
				return 0;
			}
	}
	else 
		printf("出错！");	
}

int isMatch(char *password,char *password_real)
{
	int i;
	for(i=0;i<16;i++)
	{
		if(password[i] == '\0' && password_real[i] == '\0')
		{
			return 1;
		}
		else 
		if (password[i] == password_real[i])
		{

		}
		else return 0;

	}
	return 1;
}

int signUp(char *number, char *password)
{
	char password_real[16];
	MYSQL ConnectorCore;
	
	printf("sign up");	

	if (createConnector(ConnectorCore) == 0)
	{
		return 0;
	}

	if(initConnector(ConnectorCore) == 0)
	{
		return 0;
	}

	if( isExist(number, password_real, ConnectorCore) == 1)
	{
		if(isMatch(password, password_real) == 1)
		{
			return 1;
		}
		else 
		{
			printf("密码错误。请重新输入");
			return 0;
		}

	}
	else 
	{
		printf("用户不存在。请重新输入");
		return 0;
	}
}


int main(void)
{
	char number[8];
	char password[16];
	
	do
	{
		printf("please enter password:\n");
		scanf("%s",password);	

		fflush(stdin);
		
		printf("please enter number:\n");
		scanf("%s",number);
			
		printf("ok");

	}while(signUp(number,password) == 0);	
}


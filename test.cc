#include "MySqlConnector.h"

int main()
{
	MySqlConnector DBconnector;
	string query = "SELECT * FROM LC_instant_messaging.im_user";
	string result = DBconnector.SelectCommand(query);
	cout<< query.c_str()<<endl;
}

#include "Login.h"

int LoginControler::InputUsrId()
{
	cout<<"please enter your account :";
	cin>>inputUserId;
	if(!IsLeagel(inputUserId))
	{
		cout<<"input ileagel, please check your input"<<endl;
		inputUserId.clear();
		this->InputUsrId();
	}
	else
	{
		return 1;
	}
}

int LoginControler::InputPassWord()
{	
	inputedPassWord.clear();
	char *passWord = getpass("please enter the password:");
	inputedPassWord(passWord);	
	return 1;
}

string LoginControler::GetUsrId()
{
	return inputedUsrId;
}

string LoginCOntroler::GetUsrPassWord()
{
	return inputedPassWord;
}

bool LoginControler::IsIleagel(string input)
{
	//检查是否有中文，非数字，长度是否符合
	if()
	{
		return true;	
	}
	else
	{
		return false;
	}
}


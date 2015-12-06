#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <string>

using namespace std;

class LoginControler
{
	public:
		int LoginGreeting();
		int InputUsrId();
		int InputPassWord();
		string EncryptPassword();
		string GetUsrId() const;
		string GetUsrPassWord() const;
	private:
		string inputedUsrId;
		string inputedPassWord;
		bool IsIleagel(string input);
};

#endif

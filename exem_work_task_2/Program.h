#pragma once
#include "dependies.h"
#include "User.h"
class Program
{
	std::vector<User> alluser;
	Admin* InWork;
	Guest* Logined;
	bool InitDB();//done
public:
	Program(); //done
	~Program();//done
	void Registration();//done
	void RegisterGuest();//done
	void RegisterAdmin();//done
	void LoginMenu();//done
	void Menu();
	void Run();
};

void Crypting_str(std::string &str);
void DeCrypting_str(std::string &str);
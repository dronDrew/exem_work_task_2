#pragma once
#include "dependies.h"
//Begin of standart classes of program
class User
{
protected:
	std::string Login;
	std::string Pass;
public:
	User();
	User(std::string Login, std::string Pass);//done
	void Save_to_DB(std::ofstream& file);
	bool operator == (User &other);//done
	bool operator != (User& other);//done
	bool SameLogin(User& other);//done
	bool SameLogin(std::string &a);//done
	std::string GetLogin();//done
	bool Set(std::string Login, std::string Pass);//done
	User& operator ->();//done
};
//class Admin
class Admin :public User {
public:
	Admin();
	Admin(std::string Login, std::string Pass);//done
	std::pair<std::string,std::string> ChangeLoginAndPass();//done
	//user controll
	std::pair<std::string, std::string>CreateNewUserLoginAndPass();//done
	std::string SelectLoginGuest();//done
	//Test controll
	bool TestControl();//done
	//done
	void GetStatistic();
};
//class Guest
class Guest :public User {
public:
	Guest();//done
	Guest(std::string Login, std::string Pass);//done
	void GetTest();//done
	void ShowStatistic();//done
	//bool Save_to_DB()override;
};
void Answear_cypt(std::string& a);//done
std::string Crypting_str_us(std::string str);//done
std::string DeCrypting_str_us(std::string str);//done
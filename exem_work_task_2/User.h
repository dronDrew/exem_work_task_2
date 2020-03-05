#pragma once
#include "dependies.h"
//Beginig of standart classes of program
class User
{
protected:
	std::string Login;
	std::string Pass;
public:
	User();
	User(std::string Login, std::string Pass);//done
	//virtual bool Save_to_DB();
	bool operator == (User &other);//done
	bool operator != (User& other);//done
	bool SameLogin(User& other);//done
	bool SameLogin(std::string &a);//done
	std::string GetLogin();//done
	User& operator ->();//done
};
//class Admin
class Admin :public User {
public:
	Admin();
	Admin(std::string Login, std::string Pass);//done
	std::pair<std::string,std::string> ChangeLoginAndPass();//done
	//user controll
	std::pair<std::string, std::string>CreateNewUserLoginAndPass();
	std::string SelectLoginGuest();
	//Test controll
	bool TestControl();//done
	bool Set(std::string Login, std::string Pass);//done
	//bool Save_to_DB()override;
};
//class Guest
class Guest :public User {
	std::string Name;
	std::string Sername;
	std::string Adress;
	std::string PhoneNumber;
public:
	Guest(std::string Login, std::string Pass);//done
	void GetTest();
	//bool Save_to_DB()override;
};
void Answear_cypt(std::string& a);
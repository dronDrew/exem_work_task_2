#pragma once
#include "dependies.h"
//Beginig of standart classes of program
class User
{
	std::string Login;
	std::string Pass;
public:
	User(std::string Login, std::string Pass);//done
	//virtual bool Save_to_DB();
	bool operator == (User &other);//done
	bool SameLogin(User& other);//done
	bool SameLogin(std::string &a);//done
};
//class Admin
class Admin :public User {
public:
	Admin(std::string Login, std::string Pass);//done
	bool ChangeLoginAndPass();
	bool UserControl();
	bool TestControl();
	void ReviewStatistic();
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
	void ReviewStatistic();
	void GetTest();
	//bool Save_to_DB()override;
};
#include "User.h"
User::User(std::string Login, std::string Pass) {
	this->Login = Login;
	this->Pass = Pass;
}
bool User::operator == (User& other) {
	return this->Login == other.Login && this->Pass == other.Pass;
}
bool User::SameLogin(User& other) {
	return this->Login == other.Login;
}
bool User::SameLogin(std::string& a ) {
	return this->Login == a;
}

Admin::Admin(std::string Login, std::string Pass) :User(Login, Pass) {}


Guest::Guest(std::string Login, std::string Pass) : User(Login, Pass) {}
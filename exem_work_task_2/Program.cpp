#include "Program.h"
//constructor
Program::Program() {
	this->current = nullptr;
	this->InitDB();
}
//destructor
Program::~Program() {
	delete this->current;
}
//init DataBase User
bool Program::InitDB() {
	std::ifstream file;
	file.open("tempAdin.bin");
	if (!file.is_open())
	{
		Admin temp("0", "0");
		this->alluser.push_back(temp);
	}
	else {
		std::string Log, Pass;
		auto size{ 0 };
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		Log.resize(size);
		file.read(reinterpret_cast<char*>(&Log.front()), sizeof(size));
		size = 0;
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		Pass.resize(size);
		file.read(reinterpret_cast<char*>(&Pass.front()), sizeof(size));
		Admin temp(Log, Pass);
		this->alluser.push_back(temp);
	}
	file.close();
	file.open("Guests.bin");
	if (!file.is_open())
	{	

	}
	else {
		while (file.eof())
		{
			std::string Log, Pass;
			auto size{ 0 };
			file.read(reinterpret_cast<char*>(&size), sizeof(size));
			Log.resize(size);
			file.read(reinterpret_cast<char*>(&Log.front()), sizeof(size));
			size = 0;
			file.read(reinterpret_cast<char*>(&size), sizeof(size));
			Pass.resize(size);
			file.read(reinterpret_cast<char*>(&Pass.front()), sizeof(size));
			Guest temp(Log, Pass);
			this->alluser.push_back(temp);
		}
	}
	file.close();
	return true;
}
//Registration
void Program::Registration() {
	Admin temp("0", "0");
	if (this->alluser[0] == temp)
	{
		this->RegisterGuest();
	}
	else
	{
		int choice{ 0 };
		std::cout << " Press 1---Register Like Admin\n" << std::endl;
		std::cout << " Press 0---Register Like new Guest\n" << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			this->RegisterAdmin();
			break;
		case 0:
			this->RegisterGuest();
			break;
		default:
			this->LoginMenu();
			break;
		}


	}



}
void Program::RegisterGuest() {
	std::string Name, Sername, Adress, Phone, Login, Pass;
	std::cout << "Register Like new Guest\n" << std::endl;
	std::cout << "Enter name\n";
	std::cin >> Name;
	std::cout << "Enter sername\n";
	std::cin >> Sername;
	std::cout << "Enter Adress\n";
	std::cin >> Adress;
	std::cout << "Enter Phonenumber\n";
	std::cin >> Phone;
	bool res = false;
	do
	{
		res = false;
		std::cout << "Enter Login\n";
		std::cin >> Login;
		for (auto elem : this->alluser)
		{
			if (elem.SameLogin(Login)) {
				std::cout << "User with this Login already exist\n";
				res = true;
			}
		}

	} while (res);
	std::cout << "Enter Pass\n";
	std::cin >> Pass;
	Guest newGuest(Login, Pass);
	this->alluser.push_back(newGuest);
	std::ofstream file;
	file.open("Guests.bin",std::ios::app);
	if (!file.is_open())
	{
		auto size = static_cast<int>(Login.size());
		file.write(reinterpret_cast<char*>(&size), sizeof(size));
		file.write(Login.data(), Login.size());
		size = static_cast<int>(Pass.size());
		file.write(reinterpret_cast<char*>(&size), sizeof(size));
		file.write(Pass.data(), Pass.size());
	}
	file.close();
}
void Program::RegisterAdmin()
{
	std::string Login, Pass;
	std::cout << "Registre like Admin\n";
	std::cout << "Enter Login\n";
	std::cin >> Login;
	std::cout << "Enter Pass\n";
	std::cin >> Pass;
	Admin NewAdmin(Login, Pass);
	this->alluser[0] = NewAdmin;
	std::ofstream file;
	file.open("tempAdin.bin");
	if (!file.is_open())
	{
		auto size = static_cast<int>(Login.size());
		file.write(reinterpret_cast<char*>(&size), sizeof(size));
		file.write(Login.data(), Login.size());
		size = static_cast<int>(Pass.size());
		file.write(reinterpret_cast<char*>(&size), sizeof(size));
		file.write(Pass.data(), Pass.size());
	}
	file.close();
}

//Login

void Program::LoginMenu() {
	std::string Login, Password;
	std::cout << "Enter Login\n";
	std::cin >> Login;
	std::cout << "Enter Password\n";
	std::cin >> Password;
	User temp(Login, Password);
	for (auto var : this->alluser)
	{
		if (temp==var&&temp==this->alluser[0])
		{
			this->current = new Admin(Login, Password);
		}
		else if(temp==var)
		{
			this->current = new Guest(Login, Password);
		}
	}
	this->Registration();
}
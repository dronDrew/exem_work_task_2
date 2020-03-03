#include "Program.h"
//crypting and decrypting func
void Crypting_str(std::string &str) {
	for (int i = 0; i < str.length(); i++)
	{
		if (i % 2) {
			str[i] = str[i] + 7;
		}
		else
		{
			str[i] = str[i] - 7;
		}
	}

}
void DeCrypting_str(std::string &str) {
	for (int i = 0; i < str.length(); i++)
	{
		if (i % 2) {
			str[i] = str[i] - 7;
		}
		else
		{
			str[i] = str[i] + 7;
		}
	}

}

//constructor
Program::Program() {
	this->InWork = nullptr;
	this->Logined = nullptr;
	this->InitDB();
}
//destructor
Program::~Program() {
	if (this->InWork == nullptr) {
		delete this->Logined;
	}
	else
	{
		delete this->InWork;
	}
}
//init DataBase User
bool Program::InitDB() {
	std::ifstream file;
	file.open("tempAdin.bin", std::ios::binary);
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
		file.read(reinterpret_cast<char*>(&Log.front()),size);
		size = 0;
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		Pass.resize(size);
		file.read(reinterpret_cast<char*>(&Pass.front()), size);
		DeCrypting_str(Log);
		DeCrypting_str(Pass);
		Admin temp(Log, Pass);
		this->alluser.push_back(temp);
	}
	file.close();
	file.open("Guests.bin",std::ios::binary);
	if (!file.is_open())
	{	

	}
	else {
		while (!file.eof())
		{
			std::string Log, Pass;
			auto size{ 0 };
			file.read(reinterpret_cast<char*>(&size), sizeof(size));
			Log.resize(size);
			if (size==0)
			{
				break;
			}
			file.read(reinterpret_cast<char*>(&Log.front()), size);
			size = 0;
			file.read(reinterpret_cast<char*>(&size), sizeof(size));
			Pass.resize(size);
			file.read(reinterpret_cast<char*>(&Pass.front()), size);
			DeCrypting_str(Log);
			DeCrypting_str(Pass);
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
	if (this->alluser[0] != temp)
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
	Crypting_str(Login);
	Crypting_str(Pass);
	Guest newGuest(Login, Pass);
	this->alluser.push_back(newGuest);
	std::ofstream file;
	file.open("Guests.bin",std::ios::binary|std::ios::app);
	if (file.is_open())
	{
		auto size = static_cast<int>(Login.size());
		file.write(reinterpret_cast<char*>(&size), sizeof(size));
		file.write(Login.data(), Login.size());
		size = static_cast<int>(Pass.size());
		file.write(reinterpret_cast<char*>(&size), sizeof(size));
		file.write(Pass.data(), Pass.size());
	}
	file.close();
	file.open("Guests_info.txt",std::ios::app);
	if (file.is_open()) {
		file << Name << std::endl;
		file << Sername << std::endl;
		file << Adress << std::endl;
		file << Phone << std::endl;
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
	Crypting_str(Login);
	Crypting_str(Pass);
	Admin NewAdmin(Login, Pass);
	this->alluser[0] = NewAdmin;
	std::ofstream file;
	file.open("tempAdin.bin", std::ios::binary);
	if (file.is_open())
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
			this->InWork = new Admin(Login, Password);
		}
		else if(temp==var)
		{
			this->Logined = new Guest(Login, Password);
		}
	}
	if (this->InWork!=nullptr||this->Logined!=nullptr)
	{
		this->Menu();
	}
	else
	{
		this->Registration();
	}
	
}
//Menu
void  Program::Menu() {
	if (this->InWork!=nullptr)
	{
		//Menu for Admin
	}
	else {
	   //Menu for Guest
	
	
	}

}
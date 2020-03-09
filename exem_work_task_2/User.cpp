#include "User.h"
//crypting ansews of test
void Answear_cypt(std::string& a) {
	for (int i = 0; i < a.length(); i++)
	{
		if (i % 2) {
			a[i] += 3;
		}
		else
		{
			a[i] -= 2;
		}
	}

}
void Answear_Decypt(std::string& a) {
	for (int i = 0; i < a.length(); i++)
	{
		if (i % 2) {
			a[i] -= 3;
		}
		else
		{
			a[i] += 2;
		}
	}

}
//crypting and decrypting func
std::string Crypting_str_us(std::string str) {
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
	return str;

}
std::string DeCrypting_str_us(std::string str) {
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
	return str;

}

//User
User::User(std::string Login, std::string Pass) {
	this->Login = Login;
	this->Pass = Pass;
}
User::User() {}
bool User::operator == (User& other) {
	return this->Login == other.Login && this->Pass == other.Pass;
}
bool User::operator != (User& other) {
	return this->Login != other.Login && this->Pass != other.Pass;
}
User& User::operator ->() {
return *this;
}
bool User::SameLogin(User& other) {
	return this->Login == other.Login;
}
bool User::SameLogin(std::string& a ) {
	return this->Login == a;
}
std::string User::GetLogin() {
	return this->Login;
}
bool User::Set(std::string Login, std::string Pass) {
	this->Login = Login;
	this->Pass = Pass;
	return true;
}
void User::Save_to_DB(std::ofstream& file) {
	std::string Log, Pass;
	Log=Crypting_str_us(this->Login);
	Pass=Crypting_str_us(this->Pass);
	auto size = static_cast<int>(Log.size());
	file.write(reinterpret_cast<char*>(&size), sizeof(size));
	file.write(Log.data(), Log.size());
	size = static_cast<int>(Pass.size());
	file.write(reinterpret_cast<char*>(&size), sizeof(size));
	file.write(Pass.data(),Pass.size());
}
//Admin
Admin::Admin(std::string Login, std::string Pass) :User(Login, Pass) {}
Admin::Admin():User(){}
std::pair<std::string, std::string> Admin::ChangeLoginAndPass() {
	std::string Login, Pass;
	std::cout << "Changing Admin  Info\n";
	std::cout << "Enter New Login\n";
	std::cin >> Login;
	std::cout << "Enter New Pass (6 symbols)\n";
	int i = 0;
	while (i < 6)
	{
		Pass += _getch();
		std::cout << "*";
		i++;
	}
	std::cout << "\n";
	std::pair<std::string, std::string>newinfo(Login, Pass);
	return newinfo;

}
void::Admin::GetStatistic() {
	std::ifstream file_statist;
	std::string info;
	std::set<std::string> DB;
	file_statist.open("Statistic.txt");
	if (!file_statist.is_open())
	{
		std::cout << "Statistic is empty\n";
	}
	else {
		while (!file_statist.eof())
		{
			std::getline(file_statist, info);
			if (file_statist.eof()) {
				break;
			}
			DB.insert(info);
		}
		file_statist.close();
		for (auto i =DB.begin(); i != DB.end(); i++)
		{
			std::cout << *i << std::endl;
		}
	}
}
bool Admin::TestControl() {
	char a;
	int choice{ 0 };
	std::ofstream file_in;
	std::ifstream file_out;
	std::string info_temp_manipulate;
	std::filesystem::path curr=std::filesystem::current_path();
	std::filesystem::path temp;
	std::cout << " Press 1 Create Category of test\n";//done
	std::cout << " Press 2 Import test\n";//done
	std::cout << " Press 3 Create test\n";//done
	std::cout << " Press 4 Add question\n";//done
	std::cin >> choice;
	switch (choice)
	{
	case 1:
		std::cout << "Enter name of category:\n";
		std::cin >> info_temp_manipulate;
		std::filesystem::create_directory(curr / info_temp_manipulate);
		break;
	case 2:
		std::cout << "Enter name of category in witch you want import file:\n";
		std::cin >> info_temp_manipulate;
		curr /= info_temp_manipulate;
		std::cout << "Enter full path to test  witch you want import\n";
		std::cin >> info_temp_manipulate;
		temp = info_temp_manipulate;
		std::cout << "Enter name of test with extension:\n";
		std::cin >> info_temp_manipulate;
		temp /= info_temp_manipulate;
		curr /= temp.filename();
		file_out.open(temp);
		file_in.open(curr);
		while (!file_out.eof())
		{
			std::getline(file_out,info_temp_manipulate);
			if (file_out.eof()) {
				break;
			}
			file_in << info_temp_manipulate;
			file_in << "\n";
		}
		file_out.close();
		file_in.close();
		std::filesystem::remove(temp);
		break;
	case 3:
		std::cout << "Enter name of caregory in wich you want create test:\n";
		std::cin >> info_temp_manipulate;
		curr /= info_temp_manipulate;
		std::cout << "Enter name of test with Extension\n";
		std::cin >> info_temp_manipulate;
		curr /= info_temp_manipulate;
		file_in.open(curr);
		if (!file_in.is_open())
		{
			std::cout << "Can`t create test\n";
			file_in.close();
		}
		else
		{
			choice = 0;
			while (choice < 12)
			{
				std::cout << "Enter question:\n";
				if (choice == 0) {
					std::cin.ignore();
				}
				std::getline(std::cin, info_temp_manipulate);
				file_in << info_temp_manipulate;
				file_in << "\n";
				std::cout << "Enter correct answer\n";
				std::getline(std::cin, info_temp_manipulate);
				Answear_cypt(info_temp_manipulate);
				file_in << info_temp_manipulate;
				file_in << "\n";
				choice++;
			}
			file_in.close();
			curr = std::filesystem::current_path();
		}
		break;
	case 4:
		std::cout << "Enter name a subject in witch you want to add questions and answers :\n";
		std::cin >> info_temp_manipulate;
		curr /= info_temp_manipulate;
		std::cout << "Enter name of test with extension\n";
		std::cin >> info_temp_manipulate;
		curr /= info_temp_manipulate;
		file_in.open(curr,std::ofstream::app);
		std::cin.ignore();
		do {
			std::cout << "Enter question:\n";
			std::getline(std::cin, info_temp_manipulate);
			file_in << info_temp_manipulate;
			file_in << "\n";
			std::cout << "Enter correct answer\n";
			std::getline(std::cin, info_temp_manipulate);
			Answear_cypt(info_temp_manipulate);
			file_in << info_temp_manipulate;
			file_in << "\n";
			std::cout << "Enter ESC to Exit and Enter to go on\n";
		} while (_getch() != 27);
		file_in.close();
		break;
	default:
		break;
	}
	return true;
}
std::pair<std::string, std::string>Admin::CreateNewUserLoginAndPass() {
	int passLenght{ 6 };
	std::string LoginForcreating, PassToLogin;
	std::cout << "Enter Login for new User\n";
	std::cin >> LoginForcreating;
	std::cout << "Enter Pass for this user(6 symbols)\n";
	while (passLenght>0)
	{
		PassToLogin += _getch();
		std::cout << "*";
		passLenght--;
	}
	std::pair<std::string, std::string>res(LoginForcreating, PassToLogin);
	return res;

}
std::string Admin::SelectLoginGuest() {
	std::string selectedLogin;
	std::cin >> selectedLogin;
	return selectedLogin;
}
//Guest
Guest::Guest(std::string Login, std::string Pass) : User(Login, Pass) {}
Guest::Guest():User() {};

void Guest::GetTest() {
	std::string Temp_info,answers;
	std::vector<int>answ;
	std::filesystem::path curr = std::filesystem::current_path();
	std::filesystem::path tpath;
	std::filesystem::directory_iterator begin(curr);
	std::filesystem::directory_iterator end;
	std::cout << "Curses available to take test:\n";
	for (begin; begin!=end; begin++)
	{
		if (begin->is_directory())
		{
			tpath = *begin;
			if (tpath.filename() != "x64") {
				std::cout << tpath.filename() << std::endl;
			}
		}
	}
	std::cout << "Enter Name of Curse:\n";
	std::cin >> Temp_info;
	curr /= Temp_info;
	std::filesystem::directory_iterator begin_sec(curr);
	std::filesystem::directory_iterator end_sec;
	std::cout << "Test available to Get:\n";
	for (begin_sec; begin_sec != end_sec; begin_sec++)
	{
		if (begin_sec->is_regular_file())
		{
			tpath = *begin_sec;
		    std::cout << tpath.filename() << std::endl;
			
		}
	}
	std::cout << "Enter Name of test with extension:\n";
	std::cin >> Temp_info;
	curr /= Temp_info;
	std::ifstream file;
	file.open(curr);
	while (!file.eof())
	{
		std::getline(file, Temp_info);
		if (answ.empty())
		{
			std::cin.ignore();
		}
		if (file.eof())
		{
			break;
		}
		std::cout << Temp_info << std::endl;
		std::getline(file, Temp_info);
		Answear_Decypt(Temp_info);
		std::getline(std::cin, answers);
		for (int i = 0; i < Temp_info.length(); i++)
		{
			Temp_info[i] = std::tolower(Temp_info[i]);
		}
		for (int i = 0; i < answers.length(); i++)
		{
			answers[i] = std::tolower(answers[i]);
		}
		if (Temp_info==answers)
		{
			answ.push_back(1);
		}
		else {
		
			answ.push_back(0);
		}
	}
	file.close();
	int res{ 0 }, total_quest{0};
	for (auto i =answ.begin(); i != answ.end(); i++)
	{
		res += *i;
	}
	total_quest = ((res * 100) / answ.size());
	if (total_quest >65)
	{
		std::cout << "You Pass Test with result : " << total_quest << std::endl;
	}
	else
	{
		std::cout << "You did not pass Test, your result : " << total_quest << std::endl;
	}
	std::ofstream file_statist;
	file_statist.open("Statistic.txt",std::ios::app);
	tpath = curr.parent_path();
	file_statist << this->Login.c_str()<<" "<<tpath.filename() << " " <<curr.filename() << " " <<total_quest<<"\n";
	file_statist.close();
}
void Guest::ShowStatistic() {
	std::string info;
	std::ifstream file_statist;
	file_statist.open("Statistic.txt");
	while (!file_statist.eof())
	{
		std::getline(file_statist, info);
		if (file_statist.eof()) {
			break;
		}
		if (info.substr(0, this->Login.length()) == this->GetLogin()) {
			std::cout << info << std::endl;
		}
	}
	
	file_statist.close();
}
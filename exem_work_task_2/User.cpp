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
bool Admin::Set(std::string Login, std::string Pass) {
	this->Login = Login;
	this->Pass = Pass;
	return true;
}
bool Admin::TestControl() {
	int choice{ 0 };
	std::ofstream file_in;
	std::ifstream file_out;
	std::string info_temp_manipulate;
	std::filesystem::path curr=std::filesystem::current_path();
	std::filesystem::path temp;
	std::cout << " Press 1 Create Category of test\n";//done
	std::cout << " Press 2 Import test\n";
	std::cout << " Press 3 Create test\n";//done
	std::cout << " Press 4 Add question\n";
	std::cin >> choice;
	switch (choice)
	{
	case 1:
		std::cout << "Enter name of category:\n";
		std::cin >> info_temp_manipulate;
		std::filesystem::create_directory(curr / info_temp_manipulate);
		break;
	case 2:
		//remake for non empty file
		std::cout << "Enter name of categoty in wich you want import file:\n";
		std::cin >> info_temp_manipulate;
		curr /= info_temp_manipulate;
		std::cout << "Enter full path to test  wich you want import\n";
		std::cin >> info_temp_manipulate;
		temp = info_temp_manipulate;
		std::cout << "Enter name of test with extension:\n";
		std::cin >> info_temp_manipulate;
		temp /= info_temp_manipulate;
		curr /= temp.filename();
		std::filesystem::rename(temp,curr);

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
				std::cin.ignore();
				std::getline(std::cin, info_temp_manipulate);
				file_in << info_temp_manipulate;
				file_in << "\n";
				std::cout << "Enter correct answer\n";
				std::cin.ignore();
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
		
		break;
	default:
		break;
	}
	return true;
}
//Guest
Guest::Guest(std::string Login, std::string Pass) : User(Login, Pass) {}
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include "Function.h"
#include "Menu.h"
#include "UsersLogAndPas.h"

Admin::Admin()
{
	Load();
}

void Admin::Save()
{
	std::ofstream outUsers("Admin.txt");

	for (size_t i = 0; i < 2; i++)
	{
		std::string s;

		if (i == 0)
			s = CypherWord(login);
		else
			s = CypherWord(password);

		for (size_t j = 0; j < s.length(); j++)
		{
			outUsers << std::bitset<8>(s[j]);
		}
		outUsers << std::endl;
	}

	outUsers.close();
}

void Admin::Load()
{
	std::ifstream inUsers("Admin.txt");
	std::string s;
	std::string a;



	int t = 0;
	int ti = 0;
	char* temp = new char[9];
	std::string ts;


	inUsers >> s;

	while (t < s.size())
	{
		s.copy(temp, 8, t);
		t += 8;
		temp[8] = '\0';
		unsigned long t2 = std::bitset<8>(temp).to_ulong();
		ts = (char)t2;
		a.append(DecypherWord(ts));
	}
	s.clear();
	login = a;
	a.clear();
	t = 0;
	ti = 0;

	inUsers >> s;

	while (t < s.size())
	{
		s.copy(temp, 8, t);
		t += 8;
		temp[8] = '\0';
		unsigned long t2 = std::bitset<8>(temp).to_ulong();
		ts = (char)t2;
		a.append(DecypherWord(ts));
	}
	s.clear();
	password = a;
	a.clear();
	t = 0;
	ti = 0;

	delete[] temp;

	inUsers.close();
}

std::string Admin::GetLogin() const
{
	return login;
}

std::string Admin::GetPassword() const
{
	return password;
}

void Admin::SetLogin(std::string l)
{
	login = l;
}

void Admin::SetPassword(std::string p)
{
	password = p;
}

void Admin::print()
{
	std::cout << "Login: " << login << " ,password: " << password << std::endl;
}

bool Admin::IsExist()
{
	if (login != "" && password != "")
		return true;
	else
		return false;
}

void Admin::AddUsers(UsersLogAndPas& _users)
{
	users = &_users;
}

void Admin::Menu()
{
	while (true)
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\tHi, admin " << login;
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		int c = Menu::select_vertical({
			"Manage tests",
			"Manipulate Users",
			"Change login/password",
			"See user statistics",
			"Change user",
			"Exit"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0:  break;
		case 1: ManipulateUsers(); break;
		case 2: ChangeLoginOrPassword(); break;
		case 3:  break;
		case 4: return; break;
		case 5: std::exit(0); std::system("pause"); break;
		}
	}
}

void Admin::ChangeLoginOrPassword()
{
	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\tChange login or password " << login;
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	int c = Menu::select_vertical({
		"Change Login",
		"Change Password",
		"Exit"
		}, HorizontalAlignment::Center, 4);
	switch (c)
	{
	case 0: ChangeLogin(); break;
	case 1: ChangePassword(); break;
	case 2: return; break;
	}
}

void Admin::ChangeLogin()
{
	std::string s;
	std::cout << "Enter your new login: ";
	std::getline(std::cin, s);
	if (users->FindLogin(s) != -1)
	{
		SetColor(ConsoleColor::Red, ConsoleColor::Black);
		std::cout << "Login already exist in users! Try another one!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		return;
	}
	login = s;

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Login has been succesfully changed to: " << login << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	Save();
	std::system("pause");
}

void Admin::ChangePassword()
{
	std::string s;
	std::cout << "Enter your old password: ";
	std::getline(std::cin, s);
	if (password != s)
	{
		SetColor(ConsoleColor::Red, ConsoleColor::Black);
		std::cout << "That's not the old password!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		return;
	}
	std::cout << "Enter your new password: ";
	std::getline(std::cin, s);
	std::string s2;
	std::cout << "Repeat your new password: ";
	std::getline(std::cin, s2);
	if (s2 != s)
	{
		SetColor(ConsoleColor::Red, ConsoleColor::Black);
		std::cout << "Passwords do not match\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		return;
	}
	password = s;

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Password has been succesfully changed" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	Save();
	std::system("pause");
}

void Admin::ManipulateUsers()
{
	while (true)
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\tManipulating Users";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		int c = Menu::select_vertical({
			"Show Users",
			"Create User",
			"Delete User",
			"Modify User",
			"Return"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0: ShowUsers(); break;
		case 1: CreateUser(); break;
		case 2: DeleteUser(); break;
		case 3: ModifyUser(); break;
		case 4: return; break;
		}
	}
}

void Admin::ShowUsers()
{
	users->print();
	std::system("pause");
}

void Admin::CreateUser()
{
	do
	{
		std::string a;
		std::string b;
		std::string c;
		std::string d;
		std::string e;

		std::cout << "Enter your login: ";
		std::getline(std::cin, a);
		if (users->FindLogin(a) != -1 || login == a)
		{
			std::cout << "Login already exist, try again\n";
			continue;
		}
		std::cout << "Enter your password: ";
		std::getline(std::cin, b);
		std::cout << "Enter your SNF: ";
		std::getline(std::cin, c);
		std::cout << "Enter your address: ";
		std::getline(std::cin, d);
		do
		{
			std::cout << "Enter your phone: ";
			std::getline(std::cin, e);

			if (e[0] != '+')
			{
				std::cout << "Phone number should start at +, try again!\n";
				continue;
			}

			if (e.length() != 13)
			{
				std::cout << "Phone number can contain only 12 digits, try again!\n";
				continue;
			}

			for (size_t p = 1; p < e.length(); p++)
			{
				if (!std::isdigit(e[p]))
				{
					std::cout << "Phone number should contain digits, try again!\n";
					continue;
				}
			}

			if (e[1] != '3' && e[2] != '8' && e[3] != '0')
			{
				std::cout << "Phone number should start at +380, try again!\n";
				continue;
			}

			break;

		} while (true);

		users->AddUser(a, b, c, d, e);
		users->Save();
		SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
		std::cout << "You've been successfully registered as user!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		break;

	} while (true);
}

void Admin::DeleteUser()
{
	int i;
	std::cout << "Enter user you want to delete, the indexes of users range from 0 to " << users->GetSize() - 1 << "(-1 to  exit): ";
	std::cin >> i;
	std::cin.ignore();
	if (i < 0 || i > users->GetSize() - 1)
	{
		SetColor(ConsoleColor::Red, ConsoleColor::Black);
		std::cout << "Index out of range!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		return;
	}
	users->DeleteUser(i);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "User succesfully deleted!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	users->Save();
	std::system("pause");
}

void Admin::ModifyUser()
{
	int i;
	int g;
	std::string s;
	std::cout << "Enter user you want to modify, the indexes of users range from 0 to " << users->GetSize() - 1 << "(-1 to  exit): ";
	std::cin >> i;
	std::cin.ignore();
	if (i < 0 || i > users->GetSize() - 1)
	{
		SetColor(ConsoleColor::Red, ConsoleColor::Black);
		std::cout << "Index out of range!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		return;
	}
	std::cout << "What do you want to change?\n1 - Login\n2 - Password\n3 - SNF\n4 - Address\n5 - Phone number\n";
	std::cin >> g;
	std::cin.ignore();
	if (g < 1 || g > 5)
	{
		SetColor(ConsoleColor::Red, ConsoleColor::Black);
		std::cout << "Index out of range!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		return;
	}
	std::cout << "Enter the new value: ";
	std::getline(std::cin, s);

	if (g == 1)
	{
		if (users->FindLogin(s) != -1 || login == s)
		{
			std::cout << "Login already exist, try again\n";
			std::system("pause");
			return;
		}
	}

	if (g == 5)
	{
		if (s[0] != '+')
		{
			std::cout << "Phone number should start at +, try again!\n";
			std::system("pause");
			return;
		}

		if (s.length() != 13)
		{
			std::cout << "Phone number can contain only 12 digits, try again!\n";
			std::system("pause");
			return;
		}

		for (size_t p = 1; p < s.length(); p++)
		{
			if (!std::isdigit(s[p]))
			{
				std::cout << "Phone number should contain digits, try again!\n";
				std::system("pause");
				return;
			}
		}

		if (s[1] != '3' && s[2] != '8' && s[3] != '0')
		{
			std::cout << "Phone number should start at +380, try again!\n";
			std::system("pause");
			return;
		}
	}
	
	users->ModifyValueInIndex(i, g - 1, s);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "User succesfully modified!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	users->Save();
	std::system("pause");

}


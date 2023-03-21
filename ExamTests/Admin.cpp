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
			"See statistics",
			"Change user",
			"Exit"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0:  break;
		case 1:  break;
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


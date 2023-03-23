#include "Application.h"
#include <iostream>
#include "Menu.h"

Application::Application()
{
	users.Load();
	admin.AddUsers(users);
	sa.Load();
	admin.AddSections(sa);
}

void Application::Menu()
{
	while (true)
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\tWelcome to Testify!";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		int c = Menu::select_vertical({
			"Login",
			"Register",
			"Register Admin",
			"Exit"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0: Login(); break;
		case 1: Register(); break;
		case 2: RegisterAdmin(); break;
		case 3: std::exit(0); std::system("pause"); break;
		}
	}
}

void Application::Login()
{
	std::string a;
	int k;
	std::cout << "Enter your login: ";
	std::getline(std::cin, a);
	if (admin.GetLogin() == a)
	{
		std::cout << "You're trying to enter admin account, please enter password: ";
		std::getline(std::cin, a);
		if (admin.GetPassword() == a)
		{
			SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
			std::cout << "Welcome to the system admin!\n";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
			std::system("pause");
			admin.Menu();
			return;
		}
		else
		{
			SetColor(ConsoleColor::Red, ConsoleColor::Black);
			std::cout << "Wrond password!\n";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
			std::system("pause");
			return;
		}
	}
	k = users.FindLogin(a);
	if (k == -1)
	{
		SetColor(ConsoleColor::Red, ConsoleColor::Black);
		std::cout << "Account with this login does not exist!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		return;
	}
	std::cout << "Enter your password: ";
	std::getline(std::cin, a);
	if (a == users.GetUsers().Brackets(k, 1))
	{
		SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
		std::cout << "Welcome to the system user!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		UI.AddUserLogAndPas(users);
		UI.GetUser().WriteInformation(users.GetUsers().Brackets(k, 0), users.GetUsers().Brackets(k, 1), users.GetUsers().Brackets(k, 2), users.GetUsers().Brackets(k, 3), users.GetUsers().Brackets(k, 4), k);
		UI.AddSectionsArray(sa);
		std::system("pause");
		UI.Menu();
		UI.GetUser().clear();
		return;
	}
	else
	{
		SetColor(ConsoleColor::Red, ConsoleColor::Black);
		std::cout << "Wrong password!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
	}
}

void Application::Register()
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
		if (users.FindLogin(a) != -1 || admin.GetLogin() == a)
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

		users.AddUser(a, b, c, d, e);
		users.Save();
		SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
		std::cout << "You've been successfully registered as user!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		break;

	} while (true);
}

void Application::RegisterAdmin()
{
	if (admin.IsExist())
	{
		std::cout << "Admin already exists! If you are an admin, please login.\n";
		std::system("pause");
		return;
	}

	std::string a;
	std::cout << "Enter your login: ";
	std::getline(std::cin, a);
	admin.SetLogin(a);
	std::cout << "Enter your password: ";
	std::getline(std::cin, a);
	admin.SetPassword(a);
	admin.Save();
	SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
	std::cout << "You've been successfully registered as admin!\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
}
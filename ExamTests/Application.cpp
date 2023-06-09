#include "Application.h"
#include <iostream>
#include "Menu.h"

Application::Application()
{
	users.Load();
	admin.AddUsers(users);
	sa.Load();
	admin.AddSections(sa);
	admin.SetUI(UI);
	UI.LoadUserInformation();
	UI.LoadHSA();
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
		//std::getline(std::cin, a);

		char helpCh;
		

		a.clear();

		while ((helpCh = _getch()) != '\r')
		{
			if (helpCh == '\b') // if backspace is pressed
			{
				if (!a.empty()) // if the string is not empty
				{
					a.pop_back(); // remove the last character from the string
					cout << "\b \b"; // erase the last * from the console output
				}
			}
			else // otherwise
			{
				a += helpCh; // append the character to the string
				cout << "*"; // print a * instead of the character
			}
		}
		cout << endl;

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
	//std::getline(std::cin, a);

	char helpCh;


	a.clear();

	while ((helpCh = _getch()) != '\r')
	{
		if (helpCh == '\b') // if backspace is pressed
		{
			if (!a.empty()) // if the string is not empty
			{
				a.pop_back(); // remove the last character from the string
				cout << "\b \b"; // erase the last * from the console output
			}
		}
		else // otherwise
		{
			a += helpCh; // append the character to the string
			cout << "*"; // print a * instead of the character
		}
	}
	cout << endl;

	if (a == users.GetUsers().Brackets(k, 1))
	{
		SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
		std::cout << "Welcome to the system user!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		UI.AddUserLogAndPas(users);
		//UI.GetUser().at(k)->WriteInformation(users.GetUsers().Brackets(k, 0), users.GetUsers().Brackets(k, 1), users.GetUsers().Brackets(k, 2), users.GetUsers().Brackets(k, 3), users.GetUsers().Brackets(k, 4));
		UI.AddSectionsArray(sa, k);
		UI.SetUIndex(k);
		std::system("pause");
		UI.Menu();
		//UI.GetUser().clear();
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
		if (a == "")
		{
			SetColor(ConsoleColor::Red, ConsoleColor::Black);
			std::cout << "Null value! Try again!\n";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
			std::system("pause");
			return;
		}
		if (users.FindLogin(a) != -1 || admin.GetLogin() == a)
		{
			SetColor(ConsoleColor::Red, ConsoleColor::Black);
			std::cout << "Login already exist, try again\n";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
			//std::system("pause");
			continue;
		}

		std::cout << "Enter your password: ";
		//std::getline(std::cin, b);

		char helpCh;


		b.clear();

		while ((helpCh = _getch()) != '\r')
		{
			if (helpCh == '\b') // if backspace is pressed
			{
				if (!b.empty()) // if the string is not empty
				{
					b.pop_back(); // remove the last character from the string
					cout << "\b \b"; // erase the last * from the console output
				}
			}
			else // otherwise
			{
				b += helpCh; // append the character to the string
				cout << "*"; // print a * instead of the character
			}
		}
		cout << endl;

		if (b == "")
		{
			SetColor(ConsoleColor::Red, ConsoleColor::Black);
			std::cout << "Null value! Try again!\n";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
			std::system("pause");
			return;
		}
		std::cout << "Enter your SNF: ";
		std::getline(std::cin, c);
		if (c == "")
		{
			SetColor(ConsoleColor::Red, ConsoleColor::Black);
			std::cout << "Null value! Try again!\n";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
			std::system("pause");
			return;
		}
		std::cout << "Enter your address: ";
		std::getline(std::cin, d);
		if (d == "")
		{
			SetColor(ConsoleColor::Red, ConsoleColor::Black);
			std::cout << "Null value! Try again!\n";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
			std::system("pause");
			return;
		}
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
		UI.AddUser(a, b, c, d, e);
		UI.GetUser().at(UI.GetUser().size() - 1)->Copy(sa);
		UI.SaveHSA();

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
	if (a == "")
	{
		SetColor(ConsoleColor::Red, ConsoleColor::Black);
		std::cout << "Null value! Try again!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		return;
	}
	admin.SetLogin(a);
	std::cout << "Enter your password: ";
	//std::getline(std::cin, a);

	char helpCh;


	a.clear();

	while ((helpCh = _getch()) != '\r')
	{
		if (helpCh == '\b')
		{
			if (!a.empty())
			{
				a.pop_back();
				cout << "\b \b";
			}
		}
		else
		{
			a += helpCh;
			cout << "*";
		}
	}
	cout << endl;

	if (a == "")
	{
		SetColor(ConsoleColor::Red, ConsoleColor::Black);
		std::cout << "Null value! Try again!\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		return;
	}
	admin.SetPassword(a);
	admin.Save();
	SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
	std::cout << "You've been successfully registered as admin!\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
}
#include "UserInterface.h"
#include <iostream>
#include "Menu.h"
#include "Function.h"
#include <iomanip>


void UserInterface::AddUserLogAndPas(UsersLogAndPas& ulap)
{
	users = ulap;
}

User& UserInterface::GetUser()
{
	return user;
}

void UserInterface::Menu()
{
	while (true)
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\tHi, " << user.GetUserInformation(0);	
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		int c = Menu::select_vertical({
			"Pass Test",
			"See previous results",
			"Change user",
			"Exit"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0:  break;
		case 1:  break;
		case 2:  return;  break;
		case 3: std::exit(0); std::system("pause"); break;
		}
	}
}

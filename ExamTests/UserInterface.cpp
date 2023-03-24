#include "UserInterface.h"
#include <iostream>
#include "Menu.h"
#include "Function.h"
#include <iomanip>
#include "QuestionFactoryPattern.h"


void UserInterface::AddUserLogAndPas(UsersLogAndPas& ulap)
{
	users = ulap;
}

void UserInterface::AddSectionsArray(SectionsArray& sa, int _uIndex)
{
	user.at(_uIndex)->SetSectionsArray(sa);
	user.at(_uIndex)->Copy();
}

std::vector<std::unique_ptr<User>>& UserInterface::GetUser()
{
	return user;
}

int UserInterface::GetUIndex()
{
	return uIndex;
}

void UserInterface::SetUIndex(int _uIndex)
{
	uIndex = _uIndex;
}

void UserInterface::Menu()
{
	while (true)
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\tHi, " << user.at(uIndex)->GetUserInformation(0);	
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		int c = Menu::select_vertical({
			"Pass Test",
			"See previous results",
			"Change user",
			"Exit"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0: DoTest();							break;
		case 1: SeeResults();						break;
		case 2: return;								break;
		case 3: std::exit(0); std::system("pause"); break;
		}
	}
}

void UserInterface::DoTest()
{

	std::vector<std::string> menu;
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to do test in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < user.at(uIndex)->GetSA()->GetSections().size(); i++)
	{
		menu.push_back(user.at(uIndex)->GetSA()->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	if (a == user.at(uIndex)->GetSA()->GetSections().size())
	{
		return;
	}

	menu.clear();
	


	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\tChoose test to pass";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);

	
	for (size_t i = 0; i < user.at(uIndex)->GetSA()->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(user.at(uIndex)->GetSA()->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	if (b == user.at(uIndex)->GetSA()->GetSection(a)->GetTests().size())
	{
		return;
	}

	menu.clear();

	for (size_t i = 0; i < user.at(uIndex)->GetSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); i++)
	{
		menu.clear();
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\t" << user.at(uIndex)->GetSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->GetName();
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		Creator* creator/* = new OneChoiceQuestionCreator*/;
		Question* constr/* = creator->create()*/;

		if (user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetType() == "OneChoiceQuestion")
		{
			creator = new OneChoiceQuestionCreator;
			constr = creator->create();
			for (size_t j = 0; j < user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetAnswers().size(); j++)
			{
				menu.push_back(user.at(uIndex)->GetSA()->GetAnswer(a, b, i, j));
			}
			menu.push_back("Cancel");
			int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);



			user.at(uIndex)->GetHSA()->SetUserAnswer(a, b, i, c, "", std::vector<int>());
		}
		else if (user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetType() == "MultipleChoiceQuestion")
		{
			for (size_t j = 0; j < user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetAnswers().size(); j++)
			{
				menu.push_back(user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetAnswers().at(j));
			}
			menu.push_back("Selected all choices");
			menu.push_back("Cancel");
			int cT;
			std::vector<int> c;
			while(true)
			{
				std::system("cls");
				SetColor(ConsoleColor::Green, ConsoleColor::Black);
				std::cout << "\n\n\t\t\t\t" << user.at(uIndex)->GetSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->GetName();
				SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
				cT = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);
				if (cT == user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetAnswers().size())
				{
					break;
				}
				if (!(std::find(c.begin(), c.end(), cT) != c.end()))
				{
					c.push_back(cT);
				}
				else if (std::find(c.begin(), c.end(), cT) != c.end())
				{
					int t = 0;
					for (size_t p = 0; p < c.size(); p++)
					{
						if (c.at(p) == cT)
							break;
						t++;
					}
					c.erase(c.begin() + t);
				}
				
			}

			user.at(uIndex)->GetHSA()->SetUserAnswer(a, b, i, 0, "", c);

		}
		else if (user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetType() == "ManualChoiceQuestion")
		{
			std::string answer;
			std::cout << "\n\t\t\t\tEnter answer: ";
			std::getline(std::cin, answer);

			user.at(uIndex)->GetHSA()->SetUserAnswer(a, b, i, 0, answer, std::vector<int>());

		}
	}

	
	
	user.at(uIndex)->GetHSA()->PrintResults(a, b);
	std::system("pause");
	user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetHasPased(true);

}

void UserInterface::SeeResults()
{
}

void UserInterface::AddUser(std::string login, std::string pass, std::string pib, std::string address, std::string phoneN)
{
	std::unique_ptr<User> tempUser(new User);
	tempUser->WriteInformation(login, pass, pib, address, phoneN);
	user.push_back(std::move(tempUser));
}

int UserInterface::FindUser(std::string login)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		if (user.at(i)->GetUserInformation(0) == login)
		{
			return i;
		}
	}
	return -1;
}

void UserInterface::DeleteUser(int _uIndex)
{
	user.erase(user.begin() + _uIndex);
}

void UserInterface::ModifyValueInIndex(int _uIndex, int _valueIndex, std::string _newValue)
{
	user.at(_uIndex)->ModifyValueByIndex(_valueIndex, _newValue);
}

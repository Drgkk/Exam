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

void UserInterface::AddSectionsArray(SectionsArray& sa)
{
	user.SetSectionsArray(sa);
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
		case 0: DoTest();							break;
		case 1: SeeResults();						break;
		case 2: return;								break;
		case 3: std::exit(0); std::system("pause"); break;
		}
	}
}

void UserInterface::DoTest()
{
	int bT = user.GetSSA()->GetB();
	SectionsArray* tempSA = new SectionsArray;

	std::vector<std::string> menu;
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to do test in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < user.GetSA()->GetSections().size(); i++)
	{
		menu.push_back(user.GetSA()->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	if (a == user.GetSA()->GetSections().size())
	{
		return;
	}

	menu.clear();


	tempSA->PushSection(user.GetSA()->GetSections().at(a)->GetName());
	


	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\tChoose test to pass";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);

	
	for (size_t i = 0; i < user.GetSA()->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(user.GetSA()->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	if (b == user.GetSA()->GetSection(a)->GetTests().size())
	{
		return;
	}

	menu.clear();

	tempSA->PushTest(user.GetSA()->GetTest(a, b)->GetName(), 0);
	bT++;
	user.GetSSA()->SetB(bT);

	for (size_t i = 0; i < user.GetSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); i++)
	{
		menu.clear();
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\t" << user.GetSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->GetName();
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		Creator* creator/* = new OneChoiceQuestionCreator*/;
		Question* constr/* = creator->create()*/;

		if (user.GetSA()->GetQuestion(a, b, i)->GetType() == "OneChoiceQuestion")
		{
			creator = new OneChoiceQuestionCreator;
			constr = creator->create();
			tempSA->PushQuestion(user.GetSA()->GetQuestion(a, b, i)->GetName(), 0, 0, constr);
			for (size_t j = 0; j < user.GetSA()->GetQuestion(a, b, i)->GetAnswers().size(); j++)
			{
				menu.push_back(user.GetSA()->GetAnswer(a, b, i, j));
				tempSA->PushAnswer(user.GetSA()->GetAnswer(a, b, i, j), 0, 0, i);
			}
			menu.push_back("Cancel");
			int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);


			
			tempSA->GetSections().at(0)->GetTests().at(0)->GetQuestions().at(i)->SetMark(user.GetSA()->GetTest(a, b)->GetQuestions().at(i)->GetMark());
			

			tempSA->SetRightAnswer(0, 0, i, user.GetSA()->GetSingleChoiceRA(a, b, i));
			tempSA->SetUserAnswer(0, 0, i, c, "", std::vector<int>());
		}
		else if (user.GetSA()->GetQuestion(a, b, i)->GetType() == "MultipleChoiceQuestion")
		{
			for (size_t j = 0; j < user.GetSA()->GetQuestion(a, b, i)->GetAnswers().size(); j++)
			{
				menu.push_back(user.GetSA()->GetQuestion(a, b, i)->GetAnswers().at(j));
			}
			menu.push_back("Cancel");
			int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);


		}
		else if (user.GetSA()->GetQuestion(a, b, i)->GetType() == "ManualChoiceQuestion")
		{
			std::cout << "Enter answer: ";


		}
	}

	
	

	user.GetSSA()->PushFullSection(tempSA->GetSection(0));
	user.GetSSA()->PrintResults(bT, 0);
	std::system("pause");

}

void UserInterface::SeeResults()
{
}

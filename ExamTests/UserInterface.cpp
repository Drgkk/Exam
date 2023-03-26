#include "UserInterface.h"
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "Function.h"
#include <iomanip>
#include "QuestionFactoryPattern.h"
#include <bitset>


void UserInterface::AddUserLogAndPas(UsersLogAndPas& ulap)
{
	users = ulap;
}

void UserInterface::AddSectionsArray(SectionsArray& sa, int _uIndex)
{
	user.at(_uIndex)->SetSectionsArray(sa);
	//user.at(_uIndex)->Copy();
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

	int questionStart = 0;

	if (user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetIsContinued())
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "The system has detected a save of this test from previous session!\nWould you like to continue the previous session?\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		
		menu.push_back("Yes");
		menu.push_back("No");
		int userChoiceToContinue = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

		switch (userChoiceToContinue)
		{
		case 0:
			for (size_t r = 0; r < user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); r++)
			{
				if (user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->GetIsDone())
				{
					questionStart++;
				}
			}
			break;
		case 1:	
			user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); r++)
			{
				if (user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
			break;
		default:
			break;
		}

		menu.clear();
	}


	for (size_t i = questionStart; i < user.at(uIndex)->GetSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); i++)
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

			if (c == user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetAnswers().size())
			{
				SaveHSA();
				return;
			}


			user.at(uIndex)->GetHSA()->SetUserAnswer(a, b, i, c, "", std::vector<int>());
			user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->SetIsDone(true);
			user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetIsContinued(true);
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
				cT = Menu::select_vertical(menu, HorizontalAlignment::Center, 4, c);
				if (cT == user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetAnswers().size())
				{
					break;
				}
				if (cT == user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetAnswers().size() + 1)
				{
					SaveHSA();
					return;
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
			user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->SetIsDone(true);
			user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetIsContinued(true);

		}
		else if (user.at(uIndex)->GetSA()->GetQuestion(a, b, i)->GetType() == "ManualChoiceQuestion")
		{
			std::string answer;
			std::cout << "\n\t\t\t\tEnter answer: ";
			std::getline(std::cin, answer);

			if (answer == "")
			{
				answer = " ";
			}

			user.at(uIndex)->GetHSA()->SetUserAnswer(a, b, i, 0, answer, std::vector<int>());
			user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->SetIsDone(true);
			user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetIsContinued(true);

		}
	}

	
	user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetHasPased(true);
	user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetIsContinued(false);
	for (size_t r = 0; r < user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); r++)
	{
		if (user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->GetIsDone())
		{
			user.at(uIndex)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->SetIsDone(false);
		}
	}
	user.at(uIndex)->GetHSA()->PrintResults(a, b);
	SaveHSA();
	std::system("pause");
	

}

void UserInterface::SeeResults()
{
	user.at(uIndex)->GetHSA()->PrintAllResults();
	std::system("pause");
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

void UserInterface::LoadUserInformation()
{
	std::ifstream inUsers("UsersLogAndPas.txt");

	std::string s;
	std::string a;
	std::string b;
	std::string c;
	std::string d;
	std::string e;

	int t = 0;
	int ti = 0;
	char* temp = new char[9];
	std::string ts;
	int k = 0;
	while (inUsers >> s)
	{
		k = 0;
		a.clear();
		b.clear();
		c.clear();
		d.clear();
		e.clear();

		do
		{
			t = 0;
			ti = 0;

			while (t < s.size())
			{
				s.copy(temp, 8, t);
				t += 8;
				temp[8] = '\0';
				unsigned long t2 = std::bitset<8>(temp).to_ulong();
				ts = (char)t2;
				if (k == 0)
					a.append(DecypherWord(ts));
				else if (k == 1)
					b.append(DecypherWord(ts));
				else if (k == 2)
					c.append(ts);
				else if (k == 3)
					d.append(ts);
				else if (k == 4)
					e.append(ts);

			}
			k++;
			s.clear();
			if (k != 5)
				inUsers >> s;
		} while (k <= 4);

		std::unique_ptr<User> temp(new User);
		temp->WriteInformation(a, b, c, d, e);
		user.push_back(std::move(temp));
	}
	delete[] temp;

	inUsers.close();
}

void UserInterface::PushSection(std::string name)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		std::unique_ptr<Sections> temp(new Sections);
		temp->AddName(name);
		user.at(i)->GetHSA()->GetSections().push_back(std::move(temp));
	}
}

void UserInterface::PushTest(std::string name, int indexS)
{
	
	for (size_t i = 0; i < user.size(); i++)
	{
		std::unique_ptr<Test> temp(new Test);
		temp->AddName(name);
		user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().push_back(std::move(temp));
	}
}

void UserInterface::PushQuestion(std::string name, int indexS, int indexT, Question* questionType)
{
	
	for (size_t i = 0; i < user.size(); i++)
	{
		std::unique_ptr<Question> temp(questionType);
		temp->SetNameQuestion(name);
		user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().push_back(std::move(temp));
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetHasPased())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetHasPased(false);
		}
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetIsContinued())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().size(); r++)
			{
				if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
		}
	}
}

void UserInterface::PushAnswerU(std::string name, int indexS, int indexT, int indexQ)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(indexQ)->GetAnswers().push_back(name);
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetHasPased())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetHasPased(false);
		}
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetIsContinued())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().size(); r++)
			{
				if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
		}
	}
}

void UserInterface::SetRightAnswer(int indexS, int indexT, int indexQ, int _ra)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(indexQ)->SetRightAnswer(_ra);
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetHasPased())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetHasPased(false);
		}
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetIsContinued())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().size(); r++)
			{
				if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
		}
	}
}

void UserInterface::SetRightAnswerForMAQ(std::string s, int indexS, int indexT, int indexQ)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(indexQ)->SetRightAnswerForMAQ(s);
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetHasPased())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetHasPased(false);
		}
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetIsContinued())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().size(); r++)
			{
				if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
		}
	}
}

void UserInterface::DeleteRightAnswer(int indexS, int indexT, int indexQ, int _ra)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(indexQ)->DelRightAnswer(_ra);
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetHasPased())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetHasPased(false);
		}
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetIsContinued())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().size(); r++)
			{
				if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
		}
	}
}

void UserInterface::DeleteSection(int indexS)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().erase(user.at(i)->GetHSA()->GetSections().begin() + indexS);
	}
}

void UserInterface::DeleteTest(int indexS, int indexT)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(indexS)->DeleteTest(indexT);
	}
}

void UserInterface::DeleteQuestion(int indexS, int indexT, int indexQ)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->QuestionDelete(indexQ);
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetHasPased())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetHasPased(false);
		}
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetIsContinued())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().size(); r++)
			{
				if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
		}
	}
}

void UserInterface::DeleteAnswer(int indexS, int indexT, int indexQ, int indexA)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(indexQ)->DeleteAnswer(indexA);
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetHasPased())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetHasPased(false);
		}
		if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetIsContinued())
		{
			user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().size(); r++)
			{
				if (user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(i)->GetHSA()->GetSections().at(indexS)->GetTests().at(indexT)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
		}
	}
}

void UserInterface::ChangeSectionName(std::string name, int a)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(a)->AddName(name);
	}
}

void UserInterface::ChangeTestName(std::string name, int a, int b)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->AddName(name);
	}
}

void UserInterface::ChangeQuestionName(std::string name, int a, int b, int c)
{

	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->SetNameQuestion(name);
		if (user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetHasPased())
		{
			user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetHasPased(false);
		}
		if (user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetIsContinued())
		{
			user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); r++)
			{
				if (user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
		}
	}
	
}

void UserInterface::ChangeAnswerName(std::string name, int a, int b, int c, int d)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().at(d) = name;
		if (user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetHasPased())
		{
			user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetHasPased(false);
		}
		if (user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetIsContinued())
		{
			user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); r++)
			{
				if (user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
		}
	}
}

void UserInterface::ChangeMark(int a, int b, int c, int m)
{
	for (size_t i = 0; i < user.size(); i++)
	{
		user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->SetMark(m);
		if (user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetHasPased())
		{
			user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetHasPased(false);
		}
		if (user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetIsContinued())
		{
			user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->SetIsContinued(false);
			for (size_t r = 0; r < user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); r++)
			{
				if (user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->GetIsDone())
				{
					user.at(i)->GetHSA()->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(r)->SetIsDone(false);
				}
			}
		}
	}
}

void UserInterface::SaveHSA()
{
	ofstream outSections("SectionsArrayHSA.txt");

	for (size_t q = 0; q < user.size(); q++)
	{



		for (size_t i = 0; i < user.at(q)->GetHSA()->GetSections().size(); i++)
		{
			user.at(q)->GetHSA()->GetSections().at(i)->Save(outSections);
		}

		std::string s;

		s = "SAtyghbnuijkm";

		for (size_t j = 0; j < s.length(); j++)
		{
			outSections << std::bitset<8>(s[j]);
		}
		outSections << std::endl;
	}

	outSections.close();
}

void UserInterface::LoadHSA()
{
	
	std::ifstream inSections("SectionsArrayHSA.txt");

	for (size_t q = 0; q < user.size(); q++)
	{
		std::string s;
		std::string a;
		int schet = 0;
		while (inSections >> s)
		{
			int t = 0;
			int ti = 0;
			char* temp = new char[9];
			std::string ts;

			while (t < s.size())
			{
				s.copy(temp, 8, t);
				t += 8;
				temp[8] = '\0';
				unsigned long t2 = std::bitset<8>(temp).to_ulong();
				ts = (char)t2;
				a.append(ts);
			}

			s = a;

			if (s != "SAtyghbnuijkm")
			{
				user.at(q)->GetHSA()->PushSection(s);
			}
			else
			{
				break;
			}
			s.clear();
			a.clear();
			t = 0;
			ti = 0;

			user.at(q)->GetHSA()->GetSections().at(schet++)->Load(inSections);
		}
	}

	inSections.close();
}

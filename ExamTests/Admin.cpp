#include "Admin.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include "Function.h"
#include "Menu.h"
#include "UsersLogAndPas.h"
#include "SectionsArray.h"
#include "QuestionFactoryPattern.h"

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

void Admin::AddSections(SectionsArray& _sa)
{
	sa = &_sa;
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
		case 0: ManageTests(); break;
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

void Admin::ManageTests()
{
	while (true)
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\tManaging Tests";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		int c = Menu::select_vertical({
			"Show Tests",
			"Add",
			"Change",
			"Save",
			"Return"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0: PrintTests(); break;
		case 1: AddTests(); break;
		case 2: ChangeTests(); break;
		case 3: SaveTests(); break;
		case 4: return; break;
		}
	}
}

void Admin::PrintTests()
{
	sa->Print();
	std::system("pause");
}

void Admin::AddTests()
{
	while (true)
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\Adding Tests";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		int c = Menu::select_vertical({
			"Add Section",
			"Add Test",
			"Add Question",
			"Add Answer",
			"Add/Delete Right Answer",
			"Return"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0: AddSection(); break;
		case 1: AddTest(); break;
		case 2: AddQuestion(); break;
		case 3: AddAnswer(); break;
		case 4: AddRightAnswer(); break;
		case 5: return; break;
		}
	}
}

void Admin::AddSection()
{
	std::string s;
	std::cout << "Enter new senction name: ";
	std::getline(std::cin, s);
	sa->PushSection(s);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Section has been succesfully added!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}

void Admin::AddTest()
{
	std::string s;
	std::vector<std::string> menu;
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to add test in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (c == sa->GetSections().size())
	{
		return;
	}

	std::system("cls");
	std::cout << "Enter new test name: ";
	std::getline(std::cin, s);

	sa->PushTest(s, c);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Test has been succesfully added!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
	
}

void Admin::AddQuestion()
{
	std::string s;
	std::vector<std::string> menu;
	Creator* creator = new OneChoiceQuestionCreator;
	Question* constr;
	std::string u;

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to add question in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose test to add question in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);

	

	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();
	if (b == sa->GetSections().at(a)->GetTests().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose question type";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);

	int c = Menu::select_vertical({
			"One Choice Question",
			"Multiple Choice Question",
			"Manual Question",
			"Cancel"
		}, HorizontalAlignment::Center, 4);

	switch (c)
	{
	case 0:
		creator = new OneChoiceQuestionCreator;
		u = "One Choice";
		break;
	case 1:
		creator = new MultipleChoiceQuestionCreator;
		u = "Multiple Choice";
		break;
	case 2:
		creator = new ManualChoiceQuestionCreator;
		u = "Manual Choice";
		break;
	case 3:
		return;
		break;
	default:
		break;
	}

	constr = creator->create();

	std::system("cls");
	std::cout << "Enter new question name: ";
	std::getline(std::cin, s);

	sa->PushQuestion(s, a, b, constr);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << u << " Question has been succesfully added!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}

void Admin::AddAnswer()
{
	std::string s;
	std::vector<std::string> menu;

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to add answer in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose test to add answer in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);



	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (b == sa->GetSections().at(a)->GetTests().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose question to add answer in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);



	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (c == sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size())
		return;

	std::system("cls");
	std::cout << "Enter new answer name: ";
	std::getline(std::cin, s);

	sa->PushAnswer(s, a, b, c);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Answer has been succesfully added!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");

}

void Admin::AddRightAnswer()
{
	std::string s;
	std::vector<std::string> menu;

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to select right answer in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose test to select right answer in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);



	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (b == sa->GetSections().at(a)->GetTests().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose question to select right answer in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);



	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (c == sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Select right answer";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);

	int d;

	if (sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetType() != "ManualChoiceQuestion")
	{
		for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().size(); i++)
		{
			menu.push_back(sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().at(i));
		}
		menu.push_back("Cancel");
		d = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

		menu.clear();
	}
	else
	{
		std::cout << "\n\n\t\t\t\t";
		sa->SetRightAnswer(a, b, c, 0);
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "Right Answer has been succesfully selected for Manual Choice Question!" << "\n";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		std::system("pause");
		std::system("cls");
		return;
	}

	if (d == sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().size())
		return;

	if (sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetType() == "MultipleChoiceQuestion")
	{
		std::vector<int>& temp = sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetSRA();
		if (std::find(temp.begin(), temp.end(), d) != temp.end())
		{
			sa->DeleteRightAnswer(a, b, c, d);
			SetColor(ConsoleColor::Green, ConsoleColor::Black);
			std::cout << "Right Answer has been succesfully deleted for Multi Choice Question!" << "\n";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
			std::system("pause");
			std::system("cls");
			return;
		}
		else
		{
			sa->SetRightAnswer(a, b, c, d);
			SetColor(ConsoleColor::Green, ConsoleColor::Black);
			std::cout << "Right Answer has been succesfully selected for Multi Choice Question!" << "\n";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
			std::system("pause");
			std::system("cls");
			return;
		}
	}
	else
	{
		sa->SetRightAnswer(a, b, c, d);
	}

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Right Answer has been succesfully selected!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}

void Admin::ChangeTests()
{
	while (true)
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\Changing Tests";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		int c = Menu::select_vertical({
			"Show Tests",
			"Delete",
			"Change Name",
			"Return"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0: PrintTests(); break;
		case 1: Delete(); break;
		case 2: ChangeName(); break;
		case 3: return; break;
		}
	}
}

void Admin::SaveTests()
{
	sa->Save();

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Tests have succesfully been saved!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
}

void Admin::Delete()
{
	while (true)
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\Deleting Tests";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		int c = Menu::select_vertical({
			"Delete Section",
			"Delete Test",
			"Delete Question",
			"Delete Answer",
			"Return"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0: DeleteSection(); break;
		case 1: DeleteTest(); break;
		case 2: DeleteQuestion(); break;
		case 3: DeleteAnswer(); break;
		case 4: return; break;
		}
	}
}

void Admin::DeleteSection()
{
	std::vector<std::string> menu;
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to delete";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
	{
		return;
	}

	std::system("cls");

	sa->DeleteSection(a);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Section has been succesfully deleted!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}

void Admin::DeleteTest()
{
	std::vector<std::string> menu;
	Creator* creator = new OneChoiceQuestionCreator;
	Question* constr;
	std::string u;

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to delete test in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose test to delete";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);



	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();
	if (b == sa->GetSections().at(a)->GetTests().size())
		return;

	std::system("cls");
	
	sa->DeleteTest(a, b);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Test has been succesfully deleted!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");

}

void Admin::DeleteQuestion()
{
	std::vector<std::string> menu;
	Creator* creator = new OneChoiceQuestionCreator;
	Question* constr;
	std::string u;

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to delete question in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose test to delete question in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);



	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();
	if (b == sa->GetSections().at(a)->GetTests().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose question to delete";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);



	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();
	if (c == sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size())
		return;

	std::system("cls");

	sa->DeleteQuestion(a, b, c);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Question has been succesfully deleted!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}

void Admin::DeleteAnswer()
{
	std::vector<std::string> menu;
	Creator* creator = new OneChoiceQuestionCreator;
	Question* constr;
	std::string u;

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to delete answer in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose test to delete answer in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);



	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();
	if (b == sa->GetSections().at(a)->GetTests().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose question to delete answer in";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);



	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();
	if (c == sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size())
		return;

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose anwer to delete";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);



	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().at(i));
	}
	menu.push_back("Cancel");
	int d = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();
	if (d == sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().size())
		return;

	std::system("cls");

	sa->DeleteAnswer(a, b, c, d);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Answer has been succesfully deleted!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}

void Admin::ChangeName()
{
	while (true)
	{
		std::system("cls");
		SetColor(ConsoleColor::Green, ConsoleColor::Black);
		std::cout << "\n\n\t\t\t\Deleting Tests";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		int c = Menu::select_vertical({
			"Change Section Name",
			"Change Test Name",
			"Change Question Name",
			"Change Answer Name",
			"Change Mark",
			"Return"
			}, HorizontalAlignment::Center, 4);
		switch (c)
		{
		case 0: ChangeNameSection(); break;
		case 1: ChangeNameTest(); break;
		case 2: ChangeNameQuestion(); break;
		case 3: ChangeNameAnswer(); break;
		case 4: ChangeMark(); break;
		case 5: return; break;
		}
	}
}

void Admin::ChangeNameSection()
{
	std::string name;
	std::vector<std::string> menu;
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to change its name";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
	{
		return;
	}

	std::system("cls");
	std::cout << "Enter new name: ";
	std::getline(std::cin, name);

	sa->GetSections().at(a)->AddName(name);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Section name has been succesfully changed!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}

void Admin::ChangeNameTest()
{
	std::string name;
	std::vector<std::string> menu;
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to change Test Name in it";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
	{
		return;
	}

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose test to change its name";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (b == sa->GetSections().at(a)->GetTests().size())
	{
		return;
	}

	std::system("cls");
	std::cout << "Enter new name: ";
	std::getline(std::cin, name);

	sa->GetSections().at(a)->GetTests().at(b)->AddName(name);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Section name has been succesfully changed!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}

void Admin::ChangeNameQuestion()
{
	std::string name;
	std::vector<std::string> menu;
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to change Question Name in it";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
	{
		return;
	}

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose test to change Question Name in it";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (b == sa->GetSections().at(a)->GetTests().size())
	{
		return;
	}

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose question to change its name";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (c == sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size())
	{
		return;
	}

	std::system("cls");
	std::cout << "Enter new name: ";
	std::getline(std::cin, name);

	sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->SetNameQuestion(name);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Question name has been succesfully changed!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}

void Admin::ChangeNameAnswer()
{
	std::string name;
	std::vector<std::string> menu;
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to change Answer Name in it";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
	{
		return;
	}

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose test to change Answer Name in it";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (b == sa->GetSections().at(a)->GetTests().size())
	{
		return;
	}

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose question to change Answer Name in it";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (c == sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size())
	{
		return;
	}

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose answer to change its name";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().at(i));
	}
	menu.push_back("Cancel");
	int d = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (d == sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().size())
	{
		return;
	}

	std::system("cls");
	std::cout << "Enter new name: ";
	std::getline(std::cin, name);

	sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->GetAnswers().at(d) = name;

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Answer name has been succesfully changed!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}

void Admin::ChangeMark()
{
	int m;
	std::vector<std::string> menu;
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose section to change mark in it";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().size(); i++)
	{
		menu.push_back(sa->GetSections().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int a = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (a == sa->GetSections().size())
	{
		return;
	}

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose test to change mark in it";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int b = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (b == sa->GetSections().at(a)->GetTests().size())
	{
		return;
	}

	std::system("cls");
	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "\n\n\t\t\t\Choose question to change its mark";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	for (size_t i = 0; i < sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size(); i++)
	{
		menu.push_back(sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(i)->GetName());
	}
	menu.push_back("Cancel");
	int c = Menu::select_vertical(menu, HorizontalAlignment::Center, 4);

	menu.clear();

	if (c == sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().size())
	{
		return;
	}

	std::system("cls");
	std::cout << "Enter new mark: ";
	cin >> m;
	cin.ignore();

	sa->GetSections().at(a)->GetTests().at(b)->GetQuestions().at(c)->SetMark(m);

	SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << "Mark has been succesfully changed!" << "\n";
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	std::system("pause");
	std::system("cls");
}


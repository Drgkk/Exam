#include "Test.h"
#include <fstream>
#include <iostream>
#include <bitset>
#include "QuestionFactoryPattern.h"

void Test::AddName(std::string name)
{
	testName = name;
}

void Test::QuestionDelete(int index)
{
	questions.erase(questions.begin() + index);
}

void Test::Save(std::ofstream& out)
{
	std::string s;

	s = testName;

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}

	out << std::endl;

	for (size_t j = 0; j < questions.size(); j++)
	{
		questions.at(j)->Save(out);
	}

	s = "Ttyghbnuijkm";

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;
}

void Test::Load(std::ifstream& in)
{
	std::string s;
	std::string a;
	int schet = 0;
	Creator* creator;
	Question* constr;

	while (in >> s)
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
		if (s == "QOtyghbnuijkm")
		{
			creator = new OneChoiceQuestionCreator;
			constr = creator->create();

			s.clear();
			a.clear();
			t = 0;
			ti = 0;
			delete[] temp;
			temp = new char[9];
			ts.clear();

			in >> s;
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

			PushQuestion(constr, s);
		}
		else if (s == "QMatyghbnuijkm")
		{
			creator = new ManualChoiceQuestionCreator;
			constr = creator->create();

			s.clear();
			a.clear();
			t = 0;
			ti = 0;
			delete[] temp;
			temp = new char[9];
			ts.clear();

			in >> s;
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

			PushQuestion(constr, s);
		}
		else if (s == "QMutyghbnuijkm")
		{
			creator = new MultipleChoiceQuestionCreator;
			constr = creator->create();

			s.clear();
			a.clear();
			t = 0;
			ti = 0;
			delete[] temp;
			temp = new char[9];
			ts.clear();

			in >> s;
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

			PushQuestion(constr, s);
		}
		else if (s == "Ttyghbnuijkm")
		{
			return;
		}


		s.clear();
		a.clear();
		t = 0;
		ti = 0;

		questions.at(schet++)->Load(in);

		delete[] temp;
	}
}

std::vector<std::unique_ptr<Question>>& Test::GetQuestions()
{
	return questions;
}

void Test::PrintTest(int indexQ)
{
	std::cout << testName << std::endl;
	questions.at(indexQ)->Print();
}

void Test::Print()
{
	std::cout << "|----" << testName << std::endl;
	for (size_t i = 0; i < questions.size(); i++)
	{
		questions.at(i)->Print();
	}
}

void Test::PushQuestion(Question* questionType, std::string name)
{
	std::unique_ptr<Question> temp(questionType);
	temp->SetNameQuestion(name);
	questions.push_back(std::move(temp));
}

std::string Test::GetName()
{
	return testName;
}

#include "SectionsArray.h"
#include <iostream>
#include "Sections.h"
#include "Test.h"
#include "Question.h"
#include <bitset>

void SectionsArray::PushSection(std::string name)
{
	std::unique_ptr<Sections> temp(new Sections);
	temp->AddName(name);
	sections.push_back(std::move(temp));
}

void SectionsArray::AddTest(std::string name, int indexS, int indexT)
{
	sections.at(indexS)->GetTests().at(indexT)->AddName(name);
}

void SectionsArray::AddQuestion(std::string name, int indexS, int indexT, int indexQ)
{
	sections.at(indexS)->GetTests().at(indexT)->GetQuestions().at(indexQ)->SetNameQuestion(name);
}

void SectionsArray::AddAnswer(std::string name, int indexS, int indexT, int indexQ, int indexA)
{
	sections.at(indexS)->GetTests().at(indexT)->GetQuestions().at(indexQ)->GetAnswers().at(indexA).assign(name);
}

void SectionsArray::PushTest(std::string name, int indexS)
{
	std::unique_ptr<Test> temp(new Test);
	temp->AddName(name);
	sections.at(indexS)->GetTests().push_back(std::move(temp));
}

void SectionsArray::PushQuestion(std::string name, int indexS, int indexT, Question* questionType)
{
	std::unique_ptr<Question> temp(questionType);
	temp->SetNameQuestion(name);
	sections.at(indexS)->GetTests().at(indexT)->GetQuestions().push_back(std::move(temp));
}

void SectionsArray::PushAnswer(std::string name, int indexS, int indexT, int indexQ)
{
	sections.at(indexS)->GetTests().at(indexT)->GetQuestions().at(indexQ)->GetAnswers().push_back(std::move(name));
}

void SectionsArray::SetRightAnswer(int indexS, int indexT, int indexQ, int _ra)
{
	sections.at(indexS)->GetTests().at(indexT)->GetQuestions().at(indexQ)->SetRightAnswer(_ra);
}

std::vector<std::unique_ptr<Sections>>& SectionsArray::GetSections()
{
	return sections;
}

void SectionsArray::Save()
{
	ofstream outSections("SectionsArray.txt");

	for (size_t i = 0; i < sections.size(); i++)
	{
		sections.at(i)->Save(outSections);
	}

	std::string s;

	s = "SAtyghbnuijkm";

	for (size_t j = 0; j < s.length(); j++)
	{
		outSections << std::bitset<8>(s[j]);
	}
	outSections << std::endl;

	outSections.close();
}

void SectionsArray::Load()
{
	std::string s;
	std::string a;
	int schet = 0;
	std::ifstream inSections("SectionsArray.txt");
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
			PushSection(s);
		}
		else
		{
			return;
		}
		s.clear();
		a.clear();
		t = 0;
		ti = 0;

		sections.at(schet++)->Load(inSections);
	}


	inSections.close();
}

void SectionsArray::Print()
{
	for (size_t i = 0; i < sections.size(); i++)
	{
		sections.at(i)->Print();
	}
}

#include "Sections.h"
#include <fstream>
#include "Function.h"
#include <bitset>

void Sections::AddName(std::string name)
{
	sectionName = name;
}

void Sections::DeleteTest(int index)
{
	tests.erase(tests.begin() + index);
}

std::string Sections::GetName() const
{
	return sectionName;
}

void Sections::Save(std::ofstream& out)
{
	std::string s;

	s = sectionName;

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}

	out << std::endl;

	for (size_t j = 0; j < tests.size(); j++)
	{
		tests.at(j)->Save(out);
	}

	s = "Styghbnuijkm";

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;
}

void Sections::Load(std::ifstream& in)
{
	
	std::string s;
	std::string a;
	int schet = 0;

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
		if (s != "Styghbnuijkm")
		{
			PushTest(s);
		}
		else
		{
			return;
		}
		s.clear();
		a.clear();
		t = 0;
		ti = 0;

		tests.at(schet++)->Load(in);

		delete[] temp;
	}
}

std::vector<std::unique_ptr<Test>>& Sections::GetTests()
{
	return tests;
}

void Sections::Print()
{
	std::cout << sectionName << std::endl;
	for (size_t i = 0; i < tests.size(); i++)
	{
		tests.at(i)->Print();
	}
}

void Sections::PushTest(std::string name)
{
	std::unique_ptr<Test> temp(new Test);
	temp->AddName(name);
	tests.push_back(std::move(temp));
}

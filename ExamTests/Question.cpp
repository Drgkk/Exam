#include "Question.h"
#include <iostream>
#include <string>
#include "Function.h"
#include <fstream>
#include <bitset>

void Question::SetNameQuestion(std::string s)
{
	questionName = s;
}

std::vector<std::string>& Question::GetAnswers()
{
	return answers;
}

void Question::PushAnswer(std::string name)
{
	answers.push_back(name);
}

void OneChoiceQuestion::Print()
{
	std::cout << questionName << std::endl;
	for (size_t i = 0; i < answers.size(); i++)
	{
		if (i == ra)
			SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
		std::cout << answers.at(i) << std::endl;
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	}
}

void OneChoiceQuestion::SetRightAnswer(int _ra)
{
	ra = _ra;
}

void OneChoiceQuestion::Save(std::ofstream& out)
{
	std::string s;

	s = "QOtyghbnuijkm";

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;

	s = questionName;

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}

	out << std::endl;

	for (size_t j = 0; j < answers.size(); j++)
	{
		s = answers.at(j);

		for (size_t j = 0; j < s.length(); j++)
		{
			out << std::bitset<8>(s[j]);
		}

		out << std::endl;
	}

	s = "Qtyghbnuijkm";

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;

	s = std::to_string(ra);

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;
}

void OneChoiceQuestion::Load(std::ifstream& in)
{
	std::string s;
	std::string a;

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

		if (s != "Qtyghbnuijkm")
		{
			PushAnswer(s);
		}
		else
		{
			s.clear();
			a.clear();
			t = 0;
			ti = 0;
			delete[] temp;
			char* temp = new char[9];
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

			ra = std::stoi(s);
			return;
		}

		s.clear();
		a.clear();
		t = 0;
		ti = 0;

		

		delete[] temp;
	}
}

void ManualChoiceQuestion::Print()
{
	std::cout << questionName << std::endl;
	SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
	std::cout << answer << std::endl;
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
}

void ManualChoiceQuestion::SetRightAnswer(int _ra)
{
	std::cout << "Enter the right answer: ";
	std::getline(std::cin, answer);
}

void ManualChoiceQuestion::Save(std::ofstream& out)
{
	std::string s;

	s = "QMatyghbnuijkm";

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;

	s = questionName;

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}

	out << std::endl;

	/*for (size_t j = 0; j < answers.size(); j++)
	{
		s = answers.at(j);

		for (size_t j = 0; j < s.length(); j++)
		{
			out << std::bitset<8>(s[j]);
		}

		out << std::endl;
	}*/

	s = "Qtyghbnuijkm";

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;

	s = answer;

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;
}

void ManualChoiceQuestion::Load(std::ifstream& in)
{
	std::string s;
	std::string a;

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

		if (s != "Qtyghbnuijkm")
		{
			PushAnswer(s);
		}
		else
		{
			s.clear();
			a.clear();
			t = 0;
			ti = 0;
			delete[] temp;
			char* temp = new char[9];
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

			answer = s;
			return;
		}

		s.clear();
		a.clear();
		t = 0;
		ti = 0;



		delete[] temp;
	}
}

void MultipleChoiceQuestion::Print()
{
	std::cout << questionName << std::endl;
	for (size_t i = 0; i < answers.size(); i++)
	{
		if (std::find(sra.begin(), sra.end(), i) != sra.end())
			SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
		std::cout << answers.at(i) << std::endl;
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	}
}

void MultipleChoiceQuestion::SetRightAnswer(int _ra)
{
	sra.push_back(_ra);
}

void MultipleChoiceQuestion::Save(std::ofstream& out)
{
	std::string s;

	s = "QMutyghbnuijkm";

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;

	s = questionName;

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}

	out << std::endl;

	for (size_t j = 0; j < answers.size(); j++)
	{
		s = answers.at(j);

		for (size_t j = 0; j < s.length(); j++)
		{
			out << std::bitset<8>(s[j]);
		}

		out << std::endl;
	}

	s = "Qtyghbnuijkm";

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;

	for (size_t j = 0; j < sra.size(); j++)
	{
		s = std::to_string(sra.at(j));

		for (size_t e = 0; e < s.length(); e++)
		{
			out << std::bitset<8>(s[e]);
		}
		out << std::endl;
	}

	s = "QMEtyghbnuijkm";

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;
}

void MultipleChoiceQuestion::Load(std::ifstream& in)
{
	std::string s;
	std::string a;

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

		if (s != "Qtyghbnuijkm")
		{
			PushAnswer(s);
		}
		else
		{
			//int schet = 0;
			delete[] temp;
			while (s != "QMEtyghbnuijkm")
			{
				s.clear();
				a.clear();
				t = 0;
				ti = 0;
				char* temp = new char[9];
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

				if(s != "QMEtyghbnuijkm")
					sra.push_back(std::stoi(s));

				delete[] temp;
			}
			return;
		}

		s.clear();
		a.clear();
		t = 0;
		ti = 0;



		delete[] temp;
	}
}

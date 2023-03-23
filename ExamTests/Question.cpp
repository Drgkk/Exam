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

void Question::DeleteAnswer(int index)
{
	answers.erase(answers.begin() + index);
}

std::string Question::GetName()
{
	return questionName;
}

void Question::SetMark(int m)
{
	mark = m;
}

int Question::GetMark()
{
	return mark;
}

void OneChoiceQuestion::Print()
{
	std::cout << "     |----" << questionName << " (" << mark << "m) " << std::endl;
	for (size_t i = 0; i < answers.size(); i++)
	{
		if (i == ra)
			SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
		std::cout << "          |----" << answers.at(i) << std::endl;
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

	s = std::to_string(mark);

	for (size_t j = 0; j < s.length(); j++)
	{
		out << std::bitset<8>(s[j]);
	}
	out << std::endl;
}

void OneChoiceQuestion::SetUserAnswer(int _ua, std::string s, std::vector<int> _sua)
{
	ua = _ua;
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

			mark = std::stoi(s);

			return;
		}

		s.clear();
		a.clear();
		t = 0;
		ti = 0;

		

		delete[] temp;
	}
}

std::string OneChoiceQuestion::GetType()
{
	return "OneChoiceQuestion";
}

std::vector<int>& OneChoiceQuestion::GetSRA()
{
	std::vector<int> a;
	return a;
}

int OneChoiceQuestion::GetRightAnswer()
{
	return ra;
}

int OneChoiceQuestion::GetRightAnswerSCQ()
{
	return ra;
}

std::string OneChoiceQuestion::GetRightAnswerMaCQ()
{
	return std::string();
}

std::vector<int> OneChoiceQuestion::GetRightAnswerMuCQ()
{
	return std::vector<int>();
}

int OneChoiceQuestion::GetUserMark()
{
	if (ua == ra)
	{
		return mark;
	}
	else
	{
		return 0;
	}
}

void OneChoiceQuestion::DelRightAnswer(int _ra)
{
}

void ManualChoiceQuestion::Print()
{
	std::cout << "     |----" << questionName << " (" << mark << "m) " << std::endl;
	SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
	std::cout << "          |----" << answer << std::endl;
	SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
}

void ManualChoiceQuestion::SetRightAnswer(int _ra)
{
	std::cout << "Enter the right answer: ";
	std::getline(std::cin, answer);
}

void ManualChoiceQuestion::DelRightAnswer(int _ra)
{
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

	s = std::to_string(mark);

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

			mark = stoi(s);

			return;
		}

		s.clear();
		a.clear();
		t = 0;
		ti = 0;



		delete[] temp;
	}
}

void ManualChoiceQuestion::SetUserAnswer(int _ua, std::string s, std::vector<int> _sua)
{
	uanswer = s;
}


std::string ManualChoiceQuestion::GetType()
{
	return "ManualChoiceQuestion";
}

std::vector<int>& ManualChoiceQuestion::GetSRA()
{
	std::vector<int> a;
	return a;
}

int ManualChoiceQuestion::GetRightAnswerSCQ()
{
	return 0;
}

std::string ManualChoiceQuestion::GetRightAnswerMaCQ()
{
	return answer;
}

std::vector<int> ManualChoiceQuestion::GetRightAnswerMuCQ()
{
	return std::vector<int>();
}

int ManualChoiceQuestion::GetUserMark()
{
	if (answer == uanswer)
	{
		return mark;
	}
	else
	{
		return 0;
	}
}

void MultipleChoiceQuestion::Print()
{
	std::cout << "     |----" << questionName << " (" << mark << "m) " << std::endl;
	for (size_t i = 0; i < answers.size(); i++)
	{
		if (std::find(sra.begin(), sra.end(), i) != sra.end())
			SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
		std::cout << "          |----" << answers.at(i) << std::endl;
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
	}
}

void MultipleChoiceQuestion::SetRightAnswer(int _ra)
{
	sra.push_back(_ra);
}

void MultipleChoiceQuestion::DelRightAnswer(int _ra)
{
	for (size_t o = 0; o < sra.size(); o++)
	{
		if (sra.at(o) == _ra)
		{
			sra.erase(sra.begin() + o);
		}
	}
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

	s = std::to_string(mark);

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

			mark = stoi(s);

			return;
		}

		s.clear();
		a.clear();
		t = 0;
		ti = 0;



		delete[] temp;
	}
}


std::string MultipleChoiceQuestion::GetType()
{
	return "MultipleChoiceQuestion";
}

void MultipleChoiceQuestion::SetUserAnswer(int _ua, std::string s, std::vector<int> _sua)
{
	sua = _sua;
}





std::vector<int>& MultipleChoiceQuestion::GetSRA()
{
	return sra;
}

int MultipleChoiceQuestion::GetRightAnswerSCQ()
{
	return 0;
}

std::string MultipleChoiceQuestion::GetRightAnswerMaCQ()
{
	return std::string();
}

std::vector<int> MultipleChoiceQuestion::GetRightAnswerMuCQ()
{
	return sra;
}

int MultipleChoiceQuestion::GetUserMark()
{
	int k = 0;
	float ratio;
	for (size_t i = 0; i < sra.size(); i++)
	{
		if (sra.at(i) == sua.at(i))
		{
			k++;
		}
	}
	ratio = (float) k / sra.size();
	return mark * ratio;
}

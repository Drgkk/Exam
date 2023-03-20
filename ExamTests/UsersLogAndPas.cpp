#include "UsersLogAndPas.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include "Function.h"

void UsersLogAndPas::Save()
{
	std::ofstream outUsers("UsersLogAndPas.txt"/*, std::ios::in | std::ios::binary*/);

	for (size_t i = 0; i < users.GetSize(); i++)
	{
		std::string s;
		for (size_t u = 0; u < 5; u++)
		{
				
			if (u == 0 || u == 1)
				s = CypherWord(users.Brackets(i, u));
			else
				s = users.Brackets(i, u);

			for (size_t j = 0; j < s.length(); j++)
			{
				outUsers << std::bitset<8>(s[j]);
			}
			outUsers << std::endl;
		}
	}

	outUsers.close();
}

void UsersLogAndPas::Load()
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
			if(k != 5)
				inUsers >> s;
		} while (k <= 4);
		
		
		users.AddElement(a, b, c, d, e);
	}
	delete[] temp;

	inUsers.close();


}

void UsersLogAndPas::AddUser(std::string a, std::string b, std::string c, std::string d, std::string e)
{
	users.AddElement(a, b, c, d, e);
}

int UsersLogAndPas::FindLogin(std::string s)
{
	for (size_t i = 0; i < users.GetSize(); i++)
	{
		if (users.Brackets(i, 0) == s) 
		{
			return i;
		}
	}
	return -1;
}

int UsersLogAndPas::FindPassword(std::string s)
{
	for (size_t i = 0; i < users.GetSize(); i++)
	{
		if (users.Brackets(i, 1) == s)
		{
			return i;
		}
	}
	return -1;
}

DoubleArray& UsersLogAndPas::GetUsers()
{
	return users;
}




void UsersLogAndPas::print()
{
	for (size_t i = 0; i < users.GetSize(); i++)
	{

		std::cout << users.Brackets(i, 0) << " " << users.Brackets(i, 1) << " " << users.Brackets(i, 2) << " " << users.Brackets(i, 3) << " " << users.Brackets(i, 4) << std::endl;

		std::cout << std::endl;
	}
}




#pragma once
#include <iostream>
#include <fstream>
#include "DoubleArray.h"

class UsersLogAndPas
{
	DoubleArray users;

public:
	void Save();
	void Load();
	void AddUser(std::string a, std::string b, std::string c, std::string d, std::string e);
	int FindLogin(std::string s);
	int FindPassword(std::string s);
	DoubleArray& GetUsers();
	void print();
	void DeleteUser(int index);
	int GetSize();
	void ModifyValueInIndex(int i, int g, std::string s);
};


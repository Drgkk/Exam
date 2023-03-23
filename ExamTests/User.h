#pragma once
#include <iostream>
#include <vector>
#include "SectionsArray.h"

class User
{
	std::vector<std::string> userInformation;
	int r;
	SectionsArray* sa;
	SectionsArray* ssa;

public:
	User();
	void SetSectionsArray(SectionsArray& _sa);
	void WriteInformation(std::string login, std::string pass, std::string pib, std::string address, std::string phoneN, int r);
	std::string GetUserInformation(int index);
	void clear();
	SectionsArray* GetSA();
	SectionsArray* GetSSA();
};


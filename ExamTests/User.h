#pragma once
#include <iostream>
#include <vector>
#include "SectionsArray.h"

class User
{
	std::vector<std::string> userInformation;
	//int r;
	SectionsArray* sa;
	SectionsArray* ssa;
	SectionsArray* hsa;

public:
	User();
	void SetSectionsArray(SectionsArray& _sa);
	void WriteInformation(std::string login, std::string pass, std::string pib, std::string address, std::string phoneN/*, int r*/);
	std::string GetUserInformation(int index);
	void clear();
	SectionsArray* GetSA();
	SectionsArray* GetSSA();
	SectionsArray* GetHSA();
	void Copy(SectionsArray& _sa);
	void ModifyValueByIndex(int index, std::string s);
};


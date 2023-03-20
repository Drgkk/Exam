#pragma once
#include <iostream>
#include <vector>

class User
{
	std::vector<std::string> userInformation;
	int r;

public:
	void WriteInformation(std::string login, std::string pass, std::string pib, std::string address, std::string phoneN, int r);
	std::string GetUserInformation(int index);
	void clear();
};


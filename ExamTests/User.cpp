#include "User.h"

void User::WriteInformation(std::string login, std::string pass, std::string pib, std::string address, std::string phoneN, int row)
{
	userInformation.push_back(login);
	userInformation.push_back(pass);
	userInformation.push_back(pib);
	userInformation.push_back(address);
	userInformation.push_back(phoneN);
	r = row;
}

std::string User::GetUserInformation(int index)
{
	return userInformation.at(index);
}

void User::clear()
{
	userInformation.clear();
}

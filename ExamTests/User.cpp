#include "User.h"

User::User()
{
	ssa = new SectionsArray();
	hsa = new SectionsArray();
}

void User::SetSectionsArray(SectionsArray& _sa)
{
	sa = &_sa;
}

void User::WriteInformation(std::string login, std::string pass, std::string pib, std::string address, std::string phoneN/*, int row*/)
{
	userInformation.push_back(login);
	userInformation.push_back(pass);
	userInformation.push_back(pib);
	userInformation.push_back(address);
	userInformation.push_back(phoneN);
	//r = row;
}

std::string User::GetUserInformation(int index)
{
	return userInformation.at(index);
}

void User::clear()
{
	userInformation.clear();
}

SectionsArray* User::GetSA()
{
	return sa;
}

SectionsArray* User::GetSSA()
{
	return ssa;
}

SectionsArray* User::GetHSA()
{
	return hsa;
}

void User::Copy()
{
	hsa->GetSections().clear();
	*hsa = *sa;
}

void User::ModifyValueByIndex(int index, std::string s)
{
	userInformation.at(index) = s;
}

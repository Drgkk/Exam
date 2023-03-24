#pragma once
#include <iostream>
#include "User.h"
#include "UsersLogAndPas.h"
#include "SectionsArray.h" 

class UserInterface
{
	UsersLogAndPas users;
	std::vector<std::unique_ptr<User>> user;
	int uIndex;
	
public:
	void AddUserLogAndPas(UsersLogAndPas& ulap);
	void AddSectionsArray(SectionsArray& sa, int _uIndex);
	std::vector<std::unique_ptr<User>>& GetUser();
	int GetUIndex();
	void SetUIndex(int _uIndex);

	void Menu();
	void DoTest();
	void SeeResults();

	void AddUser(std::string login, std::string pass, std::string pib, std::string address, std::string phoneN);
	int FindUser(std::string login);
	void DeleteUser(int _uIndex);
	void ModifyValueInIndex(int _uIndex, int _valueIndex, std::string _newValue);
};


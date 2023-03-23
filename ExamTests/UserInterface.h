#pragma once
#include <iostream>
#include "User.h"
#include "UsersLogAndPas.h"
#include "SectionsArray.h" 

class UserInterface
{
	UsersLogAndPas users;
	User user;
	
public:
	void AddUserLogAndPas(UsersLogAndPas& ulap);
	void AddSectionsArray(SectionsArray& sa);
	User& GetUser();

	void Menu();
	void DoTest();
	void SeeResults();
};


#pragma once
#include <iostream>
#include "User.h"
#include "UsersLogAndPas.h"

class UserInterface
{
	UsersLogAndPas users;
	User user;

public:
	void AddUserLogAndPas(UsersLogAndPas& ulap);
	User& GetUser();
	void Menu();
};


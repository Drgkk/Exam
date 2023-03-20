#pragma once
#include <iostream>
#include "Menu.h"
#include "Function.h"
#include "UsersLogAndPas.h"
#include "User.h"
#include "UserInterface.h"
#include "Admin.h"

class Application
{
	UsersLogAndPas users;
	UserInterface UI;
	Admin admin;

public: 
	Application();
	void Menu();
	void Login();
	void Register();
	void RegisterAdmin();
};


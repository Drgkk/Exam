#pragma once
#include <iostream>


class Admin
{
	std::string login;
	std::string password;

public:
	Admin();
	void Save();
	void Load();
	std::string GetLogin() const;
	std::string GetPassword() const;
	void SetLogin(std::string l);
	void SetPassword(std::string p);
	void print();
	bool IsExist();

	void Menu();
};


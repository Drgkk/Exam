#pragma once
#include <iostream>
#include "UsersLogAndPas.h"
#include "SectionsArray.h"
#include "UserInterface.h"

class Admin
{
	UsersLogAndPas* users;
	std::string login;
	std::string password;
	SectionsArray* sa;
	UserInterface* UI;

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
	void AddUsers(UsersLogAndPas& _users);
	void AddSections(SectionsArray& _sa);

	void Menu();

	void ChangeLoginOrPassword();
	void ChangeLogin();
	void ChangePassword();

	void ManipulateUsers();
	void ShowUsers();
	void CreateUser();
	void DeleteUser();
	void ModifyUser();

	void ManageTests();
	void PrintTests();

	void AddTests();
	void AddSection();
	void AddTest();
	void AddQuestion();
	void AddAnswer();
	void AddRightAnswer();

	void ChangeTests();
	bool SaveTests();

	void Delete();
	void DeleteSection();
	void DeleteTest();
	void DeleteQuestion();
	void DeleteAnswer();

	void ChangeName();
	void ChangeNameSection();
	void ChangeNameTest();
	void ChangeNameQuestion();
	void ChangeNameAnswer();
	void ChangeMark();

	void SetUI(UserInterface& _UI);

	void SeeUsersStatistics();
};


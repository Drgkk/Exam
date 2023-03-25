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

	void LoadUserInformation();

	void PushSection(std::string name);
	void PushTest(std::string name, int indexS);
	void PushQuestion(std::string name, int indexS, int indexT, Question* questionType);
	void PushAnswerU(std::string name, int indexS, int indexT, int indexQ);
	void SetRightAnswer(int indexS, int indexT, int indexQ, int _ra);
	void SetRightAnswerForMAQ(std::string s, int indexS, int indexT, int indexQ);
	void DeleteRightAnswer(int indexS, int indexT, int indexQ, int _ra);

	void DeleteSection(int indexS);
	void DeleteTest(int indexS, int indexT);
	void DeleteQuestion(int indexS, int indexT, int indexQ);
	void DeleteAnswer(int indexS, int indexT, int indexQ, int indexA);
	
	void ChangeSectionName(std::string name, int a);
	void ChangeTestName(std::string name, int a, int b);
	void ChangeQuestionName(std::string name, int a, int b, int c);
	void ChangeAnswerName(std::string name, int a, int b, int c, int d);
	void ChangeMark(int a, int b, int c, int m);

	void SaveHSA();
	void LoadHSA();
};


#pragma once
#include <iostream>
#include "Function.h"
#include <fstream>
#include <vector>
#include "Sections.h"

class SectionsArray
{
	std::vector<std::unique_ptr<Sections>> sections;
	int b = -1;

public:
	void PushSection(std::string name);
	void DeleteSection(int indexS);
	void DeleteTest(int indexS, int indexT);
	void DeleteQuestion(int indexS, int indexT, int indexQ);
	void DeleteAnswer(int indexS, int indexT, int indexQ, int indexA);
	void AddTest(std::string name, int indexS, int indexT);
	void AddQuestion(std::string name, int indexS, int indexT, int indexQ);
	void AddAnswer(std::string name, int indexS, int indexT, int indexQ, int indexA);
	void PushTest(std::string name, int indexS);
	void PushQuestion(std::string name, int indexS, int indexT, Question* questionType);
	void PushAnswer(std::string name, int indexS, int indexT, int indexQ);
	void SetRightAnswer(int indexS, int indexT, int indexQ, int _ra);
	void SetUserAnswer(int indexS, int indexT, int indexQ, int _ra, std::string s, std::vector<int> _sua);
	void DeleteRightAnswer(int indexS, int indexT, int indexQ, int _ra);
	std::vector<std::unique_ptr<Sections>>& GetSections();
	void Save();
	void Load();
	void Print();
	std::unique_ptr<Sections>& GetSection(int indexS);
	std::unique_ptr<Test>& GetTest(int indexS, int indexT);
	std::unique_ptr<Question>& GetQuestion(int indexS, int indexT, int indexQ);
	std::string& GetAnswer(int indexS, int indexT, int indexQ, int indexA);

	int GetSingleChoiceRA(int indexS, int indexT, int indexQ);
	std::vector<int> GetMultipleChoiceRA(int indexS, int indexT, int indexQ);
	std::string GetManualChoiceRA(int indexS, int indexT, int indexQ);

	void PushFullSection(std::unique_ptr<Sections>& section);
	void PrintResults(int indexS, int indexT);

	int GetB();
	void SetB(int _b);
};


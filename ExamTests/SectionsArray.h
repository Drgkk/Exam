#pragma once
#include <iostream>
#include "Function.h"
#include <fstream>
#include <vector>
#include "Sections.h"

class SectionsArray
{
	std::vector<std::unique_ptr<Sections>> sections;

public:
	void PushSection(std::string name);
	void AddTest(std::string name, int indexS, int indexT);
	void AddQuestion(std::string name, int indexS, int indexT, int indexQ);
	void AddAnswer(std::string name, int indexS, int indexT, int indexQ, int indexA);
	void PushTest(std::string name, int indexS);
	void PushQuestion(std::string name, int indexS, int indexT, Question* questionType);
	void PushAnswer(std::string name, int indexS, int indexT, int indexQ);
	void SetRightAnswer(int indexS, int indexT, int indexQ, int _ra);
	std::vector<std::unique_ptr<Sections>>& GetSections();
	void Save();
	void Load();
	void Print();
};


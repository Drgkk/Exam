#pragma once
#include <iostream>
#include "Question.h"
#include <vector>
#include <fstream>

class Test
{
	std::string testName;
	std::vector<std::unique_ptr<Question>> questions;
	bool hasPased = false;

public:
	void AddName(std::string name);
	void QuestionDelete(int index);
	void Save(std::ofstream& out);
	void Load(std::ifstream& in);
	std::vector<std::unique_ptr<Question>>& GetQuestions();
	void PrintTest(int indexQ);
	void Print();
	void PushQuestion(Question* questionType, std::string name);
	std::string GetName();

	bool GetHasPased();
	void SetHasPased(bool _hasPased);
};


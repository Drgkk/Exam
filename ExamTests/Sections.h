#pragma once
#include <iostream>
#include "Test.h"
#include <fstream>
#include <vector>

class Sections
{
	std::string sectionName;
	std::vector<std::unique_ptr<Test>> tests;

public:
	void AddName(std::string name);
	std::string GetName() const;
	void Save(std::ofstream& out);
	void Load(std::ifstream& in);
	std::vector<std::unique_ptr<Test>>& GetTests();
	void Print();
	void PushTest(std::string name);
};


#pragma once
#include <iostream>
#include <vector>
#include <fstream>

class Question
{
protected:
	std::string questionName;
	std::vector<std::string> answers;

public:
	void SetNameQuestion(std::string name);
	virtual void Save(std::ofstream& out) = 0;
	virtual void Load(std::ifstream& in) = 0;
	std::vector<std::string>& GetAnswers();
	virtual void Print() = 0;
	virtual void SetRightAnswer(int _ra) = 0;
	void PushAnswer(std::string name);
};




class OneChoiceQuestion : public Question
{

	int ra;

public:
	virtual void Print() override;
	virtual void SetRightAnswer(int _ra) override;
	virtual void Save(std::ofstream& out) override;
	virtual void Load(std::ifstream& in) override;
};




class ManualChoiceQuestion : public Question
{
	std::string answer;

public:
	virtual void Print() override;
	virtual void SetRightAnswer(int _ra) override;
	virtual void Save(std::ofstream& out) override;
	virtual void Load(std::ifstream& in) override;
};



class MultipleChoiceQuestion : public Question
{
	std::vector<int> sra;

public:
	virtual void Print() override;
	virtual void SetRightAnswer(int _ra) override;
	virtual void Save(std::ofstream& out) override;
	virtual void Load(std::ifstream& in) override;
};
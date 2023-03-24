#pragma once
#include <iostream>
#include <vector>
#include <fstream>

class Question
{
protected:
	std::string questionName;
	std::vector<std::string> answers;
	int mark = 0;

public:
	void SetNameQuestion(std::string name);
	virtual void Save(std::ofstream& out) = 0;
	virtual void Load(std::ifstream& in) = 0;
	std::vector<std::string>& GetAnswers();
	virtual void Print() = 0;
	virtual void SetRightAnswer(int _ra) = 0;
	virtual void SetUserAnswer(int _ua, std::string s, std::vector<int> _sua) = 0;
	virtual void DelRightAnswer(int _ra) = 0;
	void PushAnswer(std::string name);
	void DeleteAnswer(int index);
	std::string GetName();
	virtual std::string GetType() = 0;
	virtual std::vector<int>& GetSRA() = 0;
	void SetMark(int m);
	int GetMark();

	virtual int GetRightAnswerSCQ() = 0;
	virtual std::string GetRightAnswerMaCQ() = 0;
	virtual std::vector<int> GetRightAnswerMuCQ() = 0;

	virtual float GetUserMark() = 0;
	virtual void SetManualAnswer(std::string s) = 0;
};




class OneChoiceQuestion : public Question
{

	int ra = 0;
	int ua;

public:
	virtual void Print() override;
	virtual void SetRightAnswer(int _ra) override;
	virtual void SetUserAnswer(int _ua, std::string s, std::vector<int> _sua);
	virtual void DelRightAnswer(int _ra) override;
	virtual void Save(std::ofstream& out) override;
	virtual void Load(std::ifstream& in) override;
	virtual std::string GetType() override;
	virtual std::vector<int>& GetSRA() override;
	int GetRightAnswer();

	virtual int GetRightAnswerSCQ();
	virtual std::string GetRightAnswerMaCQ();
	virtual std::vector<int> GetRightAnswerMuCQ();

	virtual float GetUserMark();
	virtual void SetManualAnswer(std::string s) override;
};




class ManualChoiceQuestion : public Question
{
	std::string answer = " ";
	std::string uanswer = " ";


public:
	virtual void Print() override;
	virtual void SetRightAnswer(int _ra) override;
	void SetUserAnswer(int _ua, std::string s, std::vector<int> _sua);
	virtual void DelRightAnswer(int _ra) override;
	virtual void Save(std::ofstream& out) override;
	virtual void Load(std::ifstream& in) override;
	virtual std::string GetType() override;
	virtual std::vector<int>& GetSRA() override;

	virtual int GetRightAnswerSCQ();
	virtual std::string GetRightAnswerMaCQ();
	virtual std::vector<int> GetRightAnswerMuCQ();

	virtual float GetUserMark();
	virtual void SetManualAnswer(std::string s) override;
};



class MultipleChoiceQuestion : public Question
{
	std::vector<int> sra;
	std::vector<int> sua;

public:
	virtual void Print() override;
	virtual void SetRightAnswer(int _ra) override;
	virtual void SetUserAnswer(int _ua, std::string s, std::vector<int> _sua);
	virtual void DelRightAnswer(int _ra) override;
	virtual void Save(std::ofstream& out) override;
	virtual void Load(std::ifstream& in) override;
	virtual std::string GetType() override;
	virtual std::vector<int>& GetSRA() override;

	virtual int GetRightAnswerSCQ();
	virtual std::string GetRightAnswerMaCQ();
	virtual std::vector<int> GetRightAnswerMuCQ();

	virtual float GetUserMark();
	virtual void SetManualAnswer(std::string s) override;
};
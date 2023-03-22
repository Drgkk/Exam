#pragma once
#include <iostream>
#include "Question.h"

class Creator
{
public:
	virtual~Creator() {}
	virtual Question* createQuestion() = 0;
	Question* create();
};

class  OneChoiceQuestionCreator : public Creator
{
public:
	virtual Question* createQuestion() override;
};

class ManualChoiceQuestionCreator : public Creator
{
public:
	virtual Question* createQuestion() override;
};

class MultipleChoiceQuestionCreator : public Creator
{
public:
	virtual Question* createQuestion() override;
};


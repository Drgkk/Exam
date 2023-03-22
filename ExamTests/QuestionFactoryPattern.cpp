#include "QuestionFactoryPattern.h"

Question* Creator::create()
{
	Question* question = this->createQuestion();
	return question;
}

Question* OneChoiceQuestionCreator::createQuestion()
{
	return new OneChoiceQuestion();
}

Question* ManualChoiceQuestionCreator::createQuestion()
{
	return new ManualChoiceQuestion();
}

Question* MultipleChoiceQuestionCreator::createQuestion()
{
	return new MultipleChoiceQuestion();
}

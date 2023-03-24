#include <iostream>
#include "UsersLogAndPas.h"
#include "DoubleArray.h"
#include <bitset>
#include "Application.h"
#include "Admin.h"
#include "SectionsArray.h"
#include "Question.h"
#include "QuestionFactoryPattern.h"

int main()
{
	Application app;

	app.Menu();

	//SectionsArray sa;
	//Creator* creator = new OneChoiceQuestionCreator;
	//Question* constr = creator->create();

	//

	///*sa.PushSection("Section 1");
	//sa.PushTest("Test 1", 0);
	//constr = creator->create();
	//sa.PushQuestion("Question 1", 0, 0, constr);
	//sa.PushAnswer("Answer 1", 0, 0, 0);
	//sa.PushAnswer("Answer 2", 0, 0, 0);
	//sa.PushAnswer("Answer 3", 0, 0, 0);
	//sa.PushAnswer("Answer 4", 0, 0, 0);
	//sa.SetRightAnswer(0, 0, 0, 2);

	//std::cout << std::endl;
	//sa.PushSection("Section 2");
	//sa.PushTest("Test 1", 1);
	//constr = creator->create();
	//sa.PushQuestion("Question 1", 1, 0, constr);
	//sa.PushAnswer("Answer 1", 1, 0, 0);
	//sa.PushAnswer("Answer 2", 1, 0, 0);
	//sa.SetRightAnswer(1, 0, 0, 0);
	//constr = creator->create();
	//sa.PushQuestion("Question 2", 1, 0, constr);
	//sa.PushAnswer("Answer 1", 1, 0, 1);
	//sa.PushAnswer("Answer 2", 1, 0, 1);
	//sa.PushAnswer("Answer 3", 1, 0, 1);
	//sa.PushAnswer("Answer 4", 1, 0, 1);
	//sa.SetRightAnswer(1, 0, 1, 1);

	//sa.PushTest("Test 2", 1);
	//creator = new MultipleChoiceQuestionCreator;
	//constr = creator->create();
	//sa.PushQuestion("Question 1", 1, 1, constr);
	//sa.PushAnswer("Answer 1", 1, 1, 0);
	//sa.PushAnswer("Answer 2", 1, 1, 0);
	//sa.PushAnswer("Answer 3", 1, 1, 0);
	//sa.SetRightAnswer(1, 1, 0, 2);
	//sa.SetRightAnswer(1, 1, 0, 0);
	//creator = new ManualChoiceQuestionCreator;
	//constr = creator->create();
	//sa.PushQuestion("Question 2", 1, 1, constr);
	//sa.SetRightAnswer(1, 1, 1, 1);*/


	////sa.Save();

	//sa.Load();
	//
	//sa.Print();
	
	/*SectionsArray* sa1 =new SectionsArray;
	sa1->PushSection("Section 1");
	sa1->PushTest("Test 1", 0);
	sa1->PushQuestion("Question 1", 0, 0, new OneChoiceQuestion);
	sa1->PushAnswer("Answer 1", 0, 0, 0);

	sa1->Print();

	std::cout << "\n\n";

	SectionsArray* sa2 = new SectionsArray;
	*sa2 = *sa1;

	sa1->Print();

	std::cout << "\n\n";

	sa2->Print();

	std::cout << "\n\n";

	sa1->PushSection("Section 2");
	sa2->PushTest("Test 2", 0);

	sa1->Print();

	std::cout << "\n\n";

	sa2->Print();

	std::cout << "\n\n";*/

	return 0;
}
#pragma once
#include <iostream>

class DoubleArray
{
	std::string** a;
	int size;

public:
	DoubleArray();
	~DoubleArray();
	DoubleArray(DoubleArray& aMain);
	DoubleArray& operator= (const DoubleArray& aMain);
	int GetSize() const;
	std::string** GetArray() const;
	void AddElement(std::string p1, std::string p2, std::string p3, std::string p4, std::string p5);
	void DeleteElement(int index);
	void print();
	int findElement(std::string s);
	std::string Brackets(int index1, int index2);
};


#include "DoubleArray.h"
#include <iostream>

DoubleArray::DoubleArray()
{
	a = new std::string* [1];
	size = 0;
}

DoubleArray::~DoubleArray()
{
	for (size_t i = 0; i < size; i++)
	{
		delete[] a[i];
	}
	delete a;
	size = 0;
}

DoubleArray::DoubleArray(DoubleArray& aMain)
{
	size = aMain.GetSize();
	a = new std::string* [size];
	for (size_t i = 0; i < size; i++)
	{
		a[i] = new std::string[5];
	}
	

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			a[i][j] = aMain.GetArray()[i][j];
		}
	}
}

DoubleArray& DoubleArray::operator=(const DoubleArray& aMain)
{
	size = aMain.GetSize();
	a = new std::string * [size];
	for (size_t i = 0; i < size; i++)
	{
		a[i] = new std::string[5];
	}


	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			a[i][j] = aMain.GetArray()[i][j];
		}
	}

	return *this;
}

void DoubleArray::DeleteElement(int index)
{
	if (index < 0 || index >= size)
	{
		return;
	}
	std::string** temp = new std::string * [size - 1];

	for (size_t i = 0; i < size - 1; i++)
	{
		temp[i] = new std::string[5];
	}

	for (size_t i = 0; i < index; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			temp[i][j] = a[i][j];
		}
	}
	
	for (size_t i = index + 1; i < size; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			temp[i - 1][j] = a[i][j];
		}
	}
	delete[] a;
	a = temp;
	size--;
}

void DoubleArray::print()
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int DoubleArray::findElement(std::string s)
{
	for (size_t i = 0; i < size; i++)
	{
		if (a[i][0] == s)
		{
			return i;
		}
	}
	return -1;
}

std::string DoubleArray::Brackets(int index1, int index2)
{
	return a[index1][index2];
}

std::string** DoubleArray::GetArray() const
{
	return a;
}

int DoubleArray::GetSize() const
{
	return size;

}

void DoubleArray::AddElement(std::string p1, std::string p2, std::string p3, std::string p4, std::string p5)
{
	std::string** temp = new std::string * [size + 1];

	for (size_t i = 0; i < size + 1; i++)
	{
		temp[i] = new std::string[5];
	}

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			temp[i][j] = a[i][j];
		}
	}
	temp[size][0] = p1;
	temp[size][1] = p2;
	temp[size][2] = p3;
	temp[size][3] = p4;
	temp[size][4] = p5;

	delete[] a;
	a = temp;
	size++;
}



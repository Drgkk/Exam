#pragma once
#include<iostream>
#include<Windows.h>

using namespace std;


enum ConsoleColor
{
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8,
	LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

void SetColor(int text, int background);

void gotoxy(int x, int y);

template<class T>
bool asc(const T& a, const T& b)
{
	return a > b;
}

std::string CypherWord(std::string b);

std::string DecypherWord(std::string b);

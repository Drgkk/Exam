#include "Function.h"


void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::string CypherWord(std::string b)
{
    char ch;
    int key = 3;
    std::string a = b;
    for (int i = 0; a[i] != '\0'; ++i) {
        ch = a[i];
        if (ch >= 'a' && ch <= 'z') {
            ch = ch + key;
            if (ch > 'z') {
                ch = ch - 'z' + 'a' - 1;
            }
            a[i] = ch;
        }
        else if (ch >= 'A' && ch <= 'Z') {
            ch = ch + key;
            if (ch > 'Z') {
                ch = ch - 'Z' + 'A' - 1;
            }
            a[i] = ch;
        }
    }
    return a;
}

std::string DecypherWord(std::string b)
{
    char ch;
    int key = 3;
    std::string a = b;
    for (int i = 0; a[i] != '\0'; ++i) {
        ch = a[i];
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - key;
            if (ch < 'a') {
                ch = ch + 'z' - 'a' + 1;
            }
            a[i] = ch;
        }
        else if (ch >= 'A' && ch <= 'Z') {
            ch = ch - key;
            if (ch < 'A') {
                ch = ch + 'Z' - 'A' + 1;
            }
            a[i] = ch;
        }
    }
    return a;
}
/***************************************
  Credit for finding this code goes to:
		  Yoav  Aharoni
	  [yoav_ah@netvision.net.il]
***************************************/

#include <iostream>
using namespace std;

#include <windows.h>
#include <process.h>

void gotoxy(int, int); // prototype
void clrscr(); // prototype

int main()
{
	// write text in 4 corners of the screen
	clrscr(); // function call
	gotoxy(10, 10); // function call
	cout << "at 10,10";
	gotoxy(10, 20); // function call
	cout << "at 10,20";
	gotoxy(20, 10); // function call
	cout << "at 20,10";
	gotoxy(20, 20); // function call
	cout << "at 20,20";
	return 0;
}

// function definition -- requires windows.h
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// function definition -- requires process.h
void clrscr()
{
	system("cls");
}
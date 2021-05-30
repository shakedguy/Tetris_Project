#pragma once
#include "Public_const_and_structs.h"
#include "Point.h"
#include "Files_Handler.h"
class MyException
{
protected:
	static constexpr size_t EXCEPTION_MASSAGE_X = 20, EXCEPTION_MASSAGE_Y = 5;
	static constexpr char INVALID_COMMAND_LINE_ARGUMENT[] = "Invalid command line argument";
	static constexpr char OPEN_FILE_ERROR[] = "Open file Error";
	static constexpr char GOOD_TEST[] = "Successful test";
	static constexpr char BAD_TEST[] = "Open file Error";

public:
	void pausedGame(bool flag)
	{
		clrscr();
		gotoxy(EXCEPTION_MASSAGE_X, EXCEPTION_MASSAGE_Y);
		cout << " The game paused without a winner...";
		gotoxy(EXCEPTION_MASSAGE_X + 1, EXCEPTION_MASSAGE_Y + 2);
		if (flag)
			cout << MyException::GOOD_TEST;
		else
			cout << MyException::BAD_TEST;
		gotoxy(EXCEPTION_MASSAGE_X - 1, EXCEPTION_MASSAGE_Y + 4);
		cout << "Press any key to return to the end Test";
		_getch();
		clrscr();
	}
	static void endGame(bool flag)
	{
		clrscr();
		gotoxy(EXCEPTION_MASSAGE_X, EXCEPTION_MASSAGE_Y);
		if (flag)
			cout << MyException::GOOD_TEST;
		else
			cout << MyException::BAD_TEST;
		gotoxy(EXCEPTION_MASSAGE_X - 2, EXCEPTION_MASSAGE_Y + 2);
		cout << "Press any key to return to the end Test";
		_getch();
		clrscr();
	}
};


class NoFilesFoundException : public MyException
{
	
};

class OpenFileException : public MyException
{
public:
	OpenFileException() { cout << MyException::OPEN_FILE_ERROR << endl; }
};

class CommandLineException :public MyException
{

public:
	void errorMessage()
	{
		cout << MyException::INVALID_COMMAND_LINE_ARGUMENT << endl << endl << endl;
	}
};


class BlocksFileEndEx :public MyException
{

public:
	void pausedGame(bool flag)
	{
		clrscr();
		gotoxy(EXCEPTION_MASSAGE_X, EXCEPTION_MASSAGE_Y);
		cout << " The game paused without a winner...";
		gotoxy(EXCEPTION_MASSAGE_X + 1, EXCEPTION_MASSAGE_Y + 2);
		if (flag)
			cout << MyException::GOOD_TEST;
		else
			cout << MyException::BAD_TEST;
		gotoxy(EXCEPTION_MASSAGE_X - 1, EXCEPTION_MASSAGE_Y + 4);
		cout << "Press any key to return to the end Test";
		_getch();
		clrscr();
	}
	static void endGame(bool flag)
	{
		clrscr();
		gotoxy(EXCEPTION_MASSAGE_X, EXCEPTION_MASSAGE_Y);
		if (flag)
			cout << MyException::GOOD_TEST;
		else
			cout << MyException::BAD_TEST;
		gotoxy(EXCEPTION_MASSAGE_X - 2, EXCEPTION_MASSAGE_Y + 2);
		cout << "Press any key to return to the end Test";
		_getch();
		clrscr();
	}
};

class MovesFileEndEx :public MyException
{

public:

};




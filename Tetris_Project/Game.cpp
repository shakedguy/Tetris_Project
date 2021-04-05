/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"

#include <list>


#include "Menu.h"

void Game::menuPage()
{
	Menu m({MENU_BOARD_POS});
	m.drawMenu();
	switch (m.getOption())
	{
	case 1:
		clearGame();
		init();
		break;
	case 2:
		if (resumeGame())
		{
			players[0].changeBlockPos({LEFT_CURRENT_BLOCK});
			players[1].changeBlockPos({RIGHT_CURRENT_BLOCK});
			drawBoards();
			run();
		}
		else
			menuPage();
		break;
	case 3:
		system("cls");
		break;
	}
}

bool Game::resumeGame()
{
	if (players[0].isLost() || players[1].isLost())
	{
		system("cls");
		gotoxy(WINNING_MASSAGE);
		cout << "The game ended, please try again" << endl;
		Sleep(1500);
		return false;
	}
	if (!gameNumber)
	{
		system("cls");
		gotoxy(WINNING_MASSAGE);
		cout << "There is no open game" << endl;
		Sleep(1500);
		return false;
	}
	return true;
}


void Game::init()
{
	gameNumber++;
	drawBoards();
	players[0].setPlayerKeys(PLAYER_ONE_KEYS);
	players[1].setPlayerKeys(PLAYER_TOW_KEYS);
	run();
}

void Game::run()
{
	char key = 0, temp = 1, temp2 = 2;
	int dir = 1;
	do
	{
		key = avoidMultipleHits();
		if ((dir = players[0].getDirection(key)) != -1)
			players[0].setDirection(dir);
		else if ((dir = players[1].getDirection(key)) != -1)
			players[1].setDirection(dir);
		avoidMultipleMoves(key, temp, temp2);
		move();
		returnDown();
		printScores();
		temp2 = temp;
		temp = key;
		Sleep(200);
	}
	while (key != ESC && (!players[0].isLost()) && (!players[1].isLost()));
	if (winningMassage())
		system("cls");
	gotoxy(WINNING_MASSAGE);
	menuPage();
	setTextColor(WHITE);
	clear_screen();
}

char Game::avoidMultipleHits()
{
	char key = 0;
	if (_kbhit())
		key = _getch();
	if(_kbhit())
	{
		key = _getch();
		for (int i = 0; i < 20 && key != ESC; i++)
		{
			if (_kbhit())
				key = _getch();
		}
	}
	return key;
}

void Game::avoidMultipleMoves(char& key, const char& temp, const char& temp2)
{
	if (temp == key && temp2 == key)
	{
		if (players[0].getDirection(key) != -1 && !players[0].isDown(key))
			players[0].setDirection(DOWN);
		else if (players[1].getDirection(key) != -1 && !players[1].isDown(key))
			players[1].setDirection(DOWN);
		players[0].getDownKey(key);
	}
}


bool Game::winningMassage()
{
	system("cls");
	gotoxy(WINNING_MASSAGE);
	if (players[0].isLost())
	{
		cout << "Congratulations " << players[1].getName() << ", you won !" << endl;
		Sleep(3000);
		return true;
	}
	if (players[1].isLost())
	{
		cout << "Congratulations " << players[0].getName() << ", you won !" << endl;
		Sleep(3000);
		return true;
	}
	return false;
}

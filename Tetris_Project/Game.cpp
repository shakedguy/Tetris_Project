/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"

#include "Menu.h"

void Game::menuPage()
{
	Menu m({ MENU_BOARD_POS });
	m.drawMenu();
	switch (m.getOption())
	{
	case 1:
		clearGame();
		init();
		break;
	case 2:
		players[0].changeBlockPos({ LEFT_CURRENT_BLOCK });
		players[1].changeBlockPos({ RIGHT_CURRENT_BLOCK });
		drawBoards();
		run();
		break;
	case 3:
		system("cls");
		break;
	}
}

void Game::init()
{
	drawBoards();
	players[0].setPlayerKeys(PLAYER_ONE_KEYS);
	players[1].setPlayerKeys(PLAYER_TOW_KEYS);
	run();
}

void Game::run()
{
	char key = 0;
	int dir = 1;
	do {
		if (_kbhit())
		{
			key = _getch();
			if ((dir = players[0].getDirection(key)) != -1)
				players[0].setDirection(dir);
			else if ((dir = players[1].getDirection(key)) != -1)
				players[1].setDirection(dir);
		}
		move();
		printScores();
		Sleep(200);
		returnDown();
	} while (key != ESC && (!players[0].isLost()) && (!players[1].isLost()));
	if (winningMassage())
		system("cls");
	menuPage();
	setTextColor(Color::WHITE);
	clear_screen();
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
	else if (players[1].isLost())
	{
		cout << "Congratulations " << players[0].getName() << ", you won !" << endl;
		Sleep(3000);
		return true;
	}
	return false;
}

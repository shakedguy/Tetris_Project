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
	printScores();
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
		Sleep(200);
		players[0].setDirection(DOWN);
		players[1].setDirection(DOWN);
	} while (key != ESC && (!players[0].isLost()) && (!players[1].isLost()));
	system("cls");
	menuPage();
	setTextColor(Color::WHITE);
	clear_screen();
}
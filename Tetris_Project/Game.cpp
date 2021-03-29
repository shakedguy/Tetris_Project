/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"


void Game::init()
{
	drawBoards();
	printScores();
	players[0].setPlayerKeys(PLAYER_ONE_KEYS);
	players[1].setPlayerKeys(PLAYER_TOW_KEYS);

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
	} while (key != ESC);

	setTextColor(Color::WHITE);
	clear_screen();
}
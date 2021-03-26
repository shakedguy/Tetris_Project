/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"

#include "Brick.h"


void Game::init()
{
	drawBoards();
	printScores();
	//players[0].setPlayerKeys(PLAYER_ONE_KEYS);
	//players[1].setPlayerKeys(PLAYER_TOW_KEYS);
}
void Game::run()
{
	char key = 0;
	int dir;
	do {
		//if (_kbhit())
		//	key = _getch();
		//{
		//	key = _getch();
		//	if ((dir = players[0].getDirection(key)) != -1)
		//		s[0].setDirection(dir);
		//	else if ((dir = players[1].getDirection(key)) != -1)
		//		s[1].setDirection(dir);
		//}
		
		move();
		//gotoxy(0, 0);
		Sleep(200);
	} while (key != ESC);

	setTextColor(Color::WHITE);
	clear_screen();
}
/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"



void Game::init()
{
	players[0].setName(1);
	players[1].setName(2);
	clear_screen();
	boards[0].drawBox(Point(LEFT_BOX_X, BOXES_Y));
	boards[0].drawBoard(Point(LEFT_BOARD_X, BOARDS_Y));
	boards[1].drawBoard(Point(RIGHT_BOARD_X, BOARDS_Y));
	boards[1].drawBox(Point(RIGHT_BOX_X, BOXES_Y));
	players[0].printScore();
	players[1].printScore();
}
void run()
{
	
}
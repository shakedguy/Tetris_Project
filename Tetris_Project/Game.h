/***************************************
	Header file for class "Game".
***************************************/
#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>

#include "Board.h"
#include "Box.h"
#include "Player.h"
#include "Public const and structs.h"

using namespace std;

class Game
{	
	enum { ESC = 27 };
	Player players[2];

private:
	void drawBoards() { players[0].drawBoard(); players[1].drawBoard(); }
	void printScores() { players[0].printScore(); players[1].printScore(); }
public:
	Game(): players{{1,{LEFT_BOARD_POS},{LEFT_BOX_POS}},{2,{RIGHT_BOARD_POS},{RIGHT_BOX_POS}}} {}
	void init();
	void run();
	void move() { players[0].move(); players[1].move(); }
};

#endif

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
	void returnDown() { players[0].setDirection(DOWN); players[1].setDirection(DOWN); }
	void drawBoards() { players[0].drawBoard(); players[1].drawBoard(); }
	void printScores() { players[0].printScore(); players[1].printScore(); }
	void clearGame() { players[0].clearGame(); players[1].clearGame(); }
	bool winningMassage();
public:
	Game(): players{{1,{LEFT_BOARD_POS},{LEFT_BOX_POS}},{2,{RIGHT_BOARD_POS},{RIGHT_BOX_POS}}} {}
	~Game() = default;
	void menuPage();
	void init();
	void run();
	void move() { players[0].move(); players[1].move(); }
};

#endif

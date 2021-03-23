/***************************************
	Header file for class "Game".
***************************************/
#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>

#include "Board.h"
#include "Player.h"
#include "Public const and structs.h"

using namespace std;

class Game
{	
	enum { ESC = 27 };
	Board boards[2] = { 0,1 };
	Player players[2] = { 0,1 };
private:
	void drawBoards() { boards[0].drawBoard(); boards[1].drawBoard(); }
public:
	void init();
	void run();
};

#endif

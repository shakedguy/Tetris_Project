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
	Board boards[2];
	Player players[2];
public:
	void init();
	void run();
};

#endif

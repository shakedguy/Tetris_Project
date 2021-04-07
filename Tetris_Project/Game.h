﻿/***************************************
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
	Player players[2];
	unsigned short int gameNumber = 0;

private:
	void returnDown() { players[0].setDirection(DEFAULT); players[1].setDirection(DEFAULT); }
	void drawBoards() { players[0].drawBoard(); players[1].drawBoard(); }
	void printScores()const { players[0].printScore(); players[1].printScore(); }
	void clearGame() { players[0].clearGame(); players[1].clearGame(); }
	bool winningMassage();
	bool resumeGame();
	void avoidMultipleMoves(char& key, const char& temp1, const char& temp2);
	char avoidMultipleHits();
	void keyAndInstructions();
	void setNames() { players[0].setName(); players[1].setName(); }
public:
	Game(): players{{1,{LEFT_BOARD_POS},{LEFT_BOX_POS}},{2,{RIGHT_BOARD_POS},{RIGHT_BOX_POS}}} {}
	~Game() = default;
	void menuPage();
	void init();
	void run();
	void move() { players[0].move(); players[1].move(); }
};

#endif

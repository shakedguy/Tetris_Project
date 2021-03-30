/***************************************
	Header file for class "Board".
***************************************/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>


#include "Block.h"
#include "Point.h"
#include "Public const and structs.h"

using namespace std;

struct Board
{
	char board[BOARD_WIDTH][BOARD_LENGTH];
	Point pos;

public:
	Board() : Board({ 0,0 }) {}
	Board(Point _pos);
	void drawBoard();
	void freezeBlock(Block& block);
	bool checkLocation(const Block& block, int direction);
};

#endif



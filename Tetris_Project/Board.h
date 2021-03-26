/***************************************
	Header file for class "Board".
***************************************/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>

#include "Point.h"
#include "Public const and structs.h"

using namespace std;

class Board
{
	Point board[BOARD_WIDTH][BOARD_LENGTH];
	Point pos;

public:
	Board() : Board({ 0,0 }) {}
	Board(Point _pos);

	void drawBoard();
	//void setPos(Point _pos) { pos.setPos(_pos.getX(), _pos.getY()); }
};

#endif



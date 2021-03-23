/***************************************
	Header file for class "Board".
***************************************/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>

#include "Box.h"
#include "Point.h"
#include "Public const and structs.h"

using namespace std;

class Board
{
	Point board[BOARD_WIDTH][BOARD_LENGTH];
	int boardNum;
	Point pos;
	Box box;

public:
	Board(int _boardNum = 0) :boardNum(_boardNum), pos(LEFT_BOARD_POS), box(boardNum)
	{
		if (boardNum)
			pos.setPos(RIGHT_BOARD_POS);
	}
	void drawBoard();
	void drawBox() { box.drawBox(); }
};

#endif



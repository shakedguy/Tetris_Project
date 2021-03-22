/***************************************
	Header file for class "Point".
***************************************/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include "Point.h"
#include "Public const and structs.h"

using namespace std;

class Board
{
	enum { WALL = 186, FLOOR = 205, UP_LEFT = 201, UP_RIGHT = 187, DOWN_LEFT = 200, DOWN_RIGHT = 188 };
	Point board[BOARD_WIDTH][BOARD_LENGTH];
	Point box[BOX_WIDTH][BOX_LENGTH];
	
public:
	void drawBoard(Point pos);
	void drawBox(Point pos);

};

#endif



/***************************************
	Header file for class "Box".
***************************************/
#ifndef _BOX_H_
#define _BOX_H_

#include <iostream>

#include "Brick.h"
#include "Point.h"
#include "Public const and structs.h"

using namespace std;

class Box
{
	Point box[BOX_WIDTH][BOX_LENGTH];
	int boxNum;
	Point pos;
	Brick bricks[3];

private:
	void drawWalls(int x, int y);
public:
	Box(int _boxNum = 0) : boxNum(_boxNum), pos(LEFT_BOX_POS)
	{
		if (boxNum)
			pos.setPos(RIGHT_BOX_POS);
		int y = 2;
		for (int i = 0; i < 3; i++)
		{
			bricks[i].setPos(Point(pos.getX() + 4, pos.getY() + y));
			y += 3;
		}	
	}
	void drawBox();
	
	
};
#endif


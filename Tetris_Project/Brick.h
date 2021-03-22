/***************************************
	Header file for class "Brick".
***************************************/
#ifndef _BRICK_H_
#define _BRICK_H_

#include <iostream>
#include "Point.h"

using namespace std;

class Brick
{
	
	Point shape[4];
	Point pos{ 0, 0 };
	int shapeNum;
public:
	Brick(Point& _pos) : pos(_pos), shapeNum(rand() % 7)
	{
		switch (shapeNum)
		{
		case 0:
			for (int i = 0; i < 4; i++)
				shape[i].setPos(pos.getX() + i, pos.getY());
			break;
		case 1:
			shape[0].setPos(pos.getX(), pos.getY());
			for (int i = 1; i < 4; i++)
				shape[i].setPos(pos.getX() + i, pos.getY() + 1);
			break;
		case 2:
			for (int i = 0; i < 3; i++)
				shape[i].setPos(pos.getX() + i, pos.getY() + 1);
			shape[0].setPos(pos.getX() + 3, pos.getY());
			break;
		case 3:
			int count = 0;
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
					shape[count++].setPos(pos.getX() + i, pos.getY() + j);
			}
			break;
			
		}
		
	}
	
};

#endif



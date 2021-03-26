/***************************************
	Header file for class "Brick".
***************************************/
#ifndef _BRICK_H_
#define _BRICK_H_

#include <iostream>
#include "Point.h"
#include "Public const and structs.h"

using namespace std;

class Brick
{
	
	Point type[4];
	Point pos;
	int shapeNum;
	int color;
	char shape;
private:
	void drawBrick0();
	void drawBrick1();
	void drawBrick2();
	void drawBrick3();
	void drawBrick4();
	void drawBrick5();
	void drawBrick6();

public:
	Brick() :Brick({ 0,0 }) {}
	Brick(Point _pos) : pos(_pos), color(0), shape(SHAPE), shapeNum(rand() % 7) {}
	void setPos(int x, int y) { pos.setPos(x, y); }
	void setPos(Point _pos) { pos.setPos(_pos.getX(), _pos.getY()); }
	void setShape(char _shape) { shape = _shape; }
	void drawBrick();
	void printBrick();
	char getShape() { return shape; }
	void move();

};

#endif



/*	Brick(Point& _pos) : pos(_pos), shapeNum(rand() % 7)
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
	*/
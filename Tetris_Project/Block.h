/***************************************
	Header file for class "Brick".
***************************************/
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <iostream>
#include <random>
#include "Point.h"
#include "Public const and structs.h"

using namespace std;


struct Block
{
	short int figure[4][4] = { {0,0,0,0},
								{0,0,0,0},
								{0,0,0,0},
								{0,0,0,0} };
	Point pos;
	char shape;
	int shapeNum;
	int color;
private:
	void set_Figure1();
	void set_Figure2();
	void set_Figure3();
	void set_Figure4();
	void set_Figure5();
	void set_Figure6();
	void set_Figure7();
	void move_Left();
	void move_Right();
	void move_Down();
	void rotate();
	void transpose_Matrix();
	void reverse_Matrix();
public:
	Block() : Block({0, 0}){}
	Block(Point _pos);
	Block& operator=(const Block& b);
	void createNewBlock();
	void setPos(int x, int y) { pos.setPos(x, y); }
	void setPos(Point _pos) { pos.setPos(_pos.getX(), _pos.getY()); }
	void setShape(char _shape) { shape = _shape; }
	void drawBlock();
	char getShape() { return shape; }
	void move(int dir);
	void cleanBlock();
	void setFigure();
	void cleanPrint();
	void copyFigure(const Block& b);
};

#endif

/***************************************
	Header file for class "Brick".
***************************************/
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <iostream>
#include "Point.h"
#include "Public const and structs.h"

using namespace std;


struct Block
{
	Point type[4];
	Point pos;
	char shape;
	int shapeNum;
	int color;
private:
	void set_Block0();
	void set_Block1();
	void set_Block2();
	void set_Block3();
	void set_Block4();
	void set_Block5();
	void set_Block6();
	void move_Left();
	void move_Right();
	void move_Down();
	void rotate();
public:
	Block() :Block({ 0,0 }) {}
	Block(Point _pos) : pos(_pos), color(0), shape(SHAPE), shapeNum(rand() % 7) { set_Brick(); }
	Block& operator=(const Block& b);
	Block& createBlock(const Point& pos);
	void setPos(int x, int y) { pos.setPos(x, y); }
	void setPos(Point _pos) { pos.setPos(_pos.getX(), _pos.getY()); }
	void setShape(char _shape) { shape = _shape; }
	void set_Brick();
	void printBrick();
	char getShape() { return shape; }
	void move(int dir);
	void cleanBlock();
	Point* getType() { return type; }
};

#endif

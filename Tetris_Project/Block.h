/***************************************
	Header file for class "Brick".
***************************************/
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <iostream>
#include <random>
#include "Point.h"
#include <array>
#include "Public const and structs.h"

using namespace std;


struct Block
{
	array<array<unsigned short int, BLOCK_MATRIX>, BLOCK_MATRIX> figure;
	Point pos;
	char shape;
	int shapeNum;
	Color color;
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
	void clockwiseRotate();
	void counterClockwiseRotate();
	void transpose_Matrix();
	void reverseColumns();
	void reverseRows();
	bool isEmptyRow(const unsigned int& row);
	void moveFifureInMatrix();
	void arrangeMatrix();

public:
	Block() : Block({0, 0}){}
	Block(Point _pos);
	Block& operator=(const Block& b);
	~Block() = default;
	void createNewBlock();
	void drawBlock();
	char getShape()const { return shape; }
	void move(int dir);
	void cleanBlock();
	void setFigure();
	void cleanPrint();
	
	
};

#endif

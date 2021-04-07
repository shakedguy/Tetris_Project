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
	array<array<ushort, BLOCK_MATRIX>, BLOCK_MATRIX> figure;
	Point pos;
	uchar shape;
	ushort shapeNum;
	Color color;

private:
	void set_Figure1();
	void set_Figure2();
	void set_Figure3();
	void set_Figure4();
	void set_Figure5();
	void set_Figure6();
	void set_Figure7();

	void transpose_Matrix();
	void reverseColumns();
	void reverseRows();
	bool isRowZeroEmpty();
	bool isColumnZeroEmpty();	
	void pullFigureUp();
	void pullFigureLeft();
	void arrangeMatrix();

public:
	Block() : Block({0, 0}){}
	Block(Point _pos);
	Block& operator=(const Block& b);
	~Block() = default;
	void createNewBlock();
	void drawBlock()const;
	uchar getShape()const { return shape; }
	void move(int dir);
	void cleanBlock();
	void setFigure();
	void cleanPrint()const;
	void clockwiseRotate();
	void counterClockwiseRotate();
	void drawMatrix();
	void DropRows(const uint& row);
	void moveLeft();
	void moveRight();
	void moveDown();
};

#endif

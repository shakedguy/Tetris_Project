/***************************************
	Header file for class "Brick".
***************************************/
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <iostream>
#include <random>
#include "Point.h"
#include <array>
//#include "Public_const_and_structs.h"

using namespace std;


class Block
{
	static bool colorsMode;
	array<array<ushort, BLOCK_MATRIX>, BLOCK_MATRIX> figure{};
	Point pos;
	uchar shape{};
	ushort shapeNum{};
	Color color;
	
	friend class Player;
	friend class Box;
	friend class Board;
	friend class Menu;

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
	Block(const Block& _block) { *this = _block; }
	Block& operator=(const Block& b);
	~Block() = default;
	friend ostream& operator<<(ostream& out, const Block& _block) { _block.drawBlock(); return out; }
	void createNewBlock();
	void drawBlock()const;
	const uchar& getShape()const { return shape; }
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
	static void changeColorsMode();
};

#endif

/***************************************
	Header file for class "Brick".
***************************************/
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Public_const_and_structs.h"
#include "Point.h"


class Block
{
	enum SHAPES { LINE, L, LEFT_L, DICE, RIGHT_STEPS, CENTER_STEP, LEFT_STEPS };
	static bool colorsMode;
	array<array<ushort, BLOCK_MATRIX>, BLOCK_MATRIX> figure;
	Point pos;
	uchar shape;
	ushort shapeNum;
	Color color;
	
	friend class Player;
	friend class Box;
	friend class Board;
	friend class Menu;
	friend class Game;

private:
	void setLineFigure();
	void setLfigure();
	void setLeftLfigure();
	void setDiceFigure();
	void setRightStepsFigure();
	void setCenterStepsFigure();
	void setLeftStepsFigure();

	void transpose_Matrix();
	void reverseRows();
	void reverseColumns();
	bool isRowZeroEmpty();
	bool isColumnZeroEmpty();	
	void pullFigureUp();
	void pullFigureLeft();
	void pullFigureRight();
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

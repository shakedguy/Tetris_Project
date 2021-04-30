/***************************************
	Header file for class "Block".
***************************************/
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Public_const_and_structs.h"
#include "Point.h"


class Block
{
	enum Shapes { LINE, L, LEFT_L, DICE, RIGHT_STEPS, CENTER_STEP, LEFT_STEPS };
	enum Filling { SHAPE = 178, SHAPE_AFTER_FREEZE = 219 };
	enum Matrix { COLUMNS = 4, ROWS = 4 };

	static bool colorsMode;
	array<array<ushort, COLUMNS>, ROWS> figure;
	Point pos;
	uchar shape;
	ushort shapeNum;
	Color color;

	friend class Player;
	friend class HumanPlayer;
	friend class ComputerPlayer;
	friend class Box;
	friend class Board;
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
	void arrangeMatrix();

public:
	Block() : Block({0, 0}) {}
	Block(Point _pos);
	Block(const Block& _block) { *this = _block; }
	Block& operator=(const Block& b);
	~Block() = default;
	friend std::ostream& operator<<(std::ostream& out, const Block& _block) { _block.drawBlock(); return out; }
	void createNewBlock();
	void drawBlock() const;
	const uchar& getShape() const { return shape; }
	void move(int dir);
	void cleanBlock();
	void setFigure();
	void cleanPrint() const;
	void clockwiseRotate();
	void counterClockwiseRotate();
	void DropRows(const uint& row);
	void moveLeft();
	void moveRight();
	void moveDown();
	static void changeColorsMode();
};

#endif

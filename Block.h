﻿/***************************************
	Header file for class "Block".
***************************************/
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Public_const_and_structs.h"
#include "Point.h"

class Block
{			/*	    #
	                   #
                        #   #      #    ##    ##   #    ## 
                        #   ###  ###    ##   ##	###    ##		*/
	enum TetrisParts { I,   L,   J,    O,   S,    T,    Z };
	enum Matrix { COLUMNS = 4, ROWS = 4 };

	static bool colorsMode;
	ushort shapeNum;
	Color color;
	friend class Player;
	friend class HumanPlayer;
	friend class ComputerPlayer;
	friend class Box;
	friend class Board;
	friend class Game;

protected:
	enum Fillings { SHAPE = 178, SHAPE_AFTER_FREEZE = 219 };
	Point pos;
	uchar shape;
	array<array<ushort, COLUMNS>, ROWS> figure;

private:
	void setShapeI();
	void setShapeL();
	void setShapeJ();
	void setShapeO();
	void setShapeS();
	void setShapeT();
	void setShapeZ();
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
	virtual ~Block() = default;
	friend std::ostream& operator<<(std::ostream& out, const Block& _block) { _block.drawBlock(); return out; }
	Block& operator=(const Block* _block) { *this = *_block; return *this; }
	void createNewBlock();
	void drawBlock() const;
	const uchar& getShape() const { return shape; }
	void move(int dir);
	void cleanBlock();
	virtual void setFigure();
	void cleanPrint() const;
	void clockwiseRotate();
	void counterClockwiseRotate();
	void moveLeft();
	void moveRight();
	void moveDown();
	bool isCleanMatrix();
	static void changeColorsMode();
	bool isColEmpty(const ushort& col)const;
};

class Bomb : public Block
{
	enum Constants { BOMB = 149, EXPLOSION_RANGE = 4 };

	friend class Board;

public:
	Bomb(const uchar& _shape = BOMB) : Bomb(_shape, { 0,0 }) {}
	Bomb(const Point& _pos) :Bomb(BOMB, { 0,0 }) {}
	Bomb(const uchar& _shape, const Point& _pos);
	~Bomb()override = default;
	Bomb& operator=(const Bomb& _bomb) { if (this != &_bomb) { Block::operator=(_bomb); return *this; } }
	void setFigure()override { figure[0][0] = shape; }
};

#endif
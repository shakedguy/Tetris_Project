/***************************************
	Header file for class "Block".
***************************************/
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Public_const_and_structs.h"
#include "Point.h"

class Block
{
protected:
		 	/*	       #
	                   #
                       #   #      #    ##    ##   #    ## 
                       #   ###  ###    ##   ##	###    ##	bomb	*/
	enum TetrisParts { I,   L,   J,    O,   S,    T,    Z,  B };
	
	static constexpr size_t COLUMNS = 4, ROWS = 4;

	static bool colorsMode;
	Color color;
	friend class Player;
	friend class HumanPlayer;
	friend class ComputerPlayer;
	friend class FilePlayer;
	friend class Box;
	friend class Board;
	friend class Game;

protected:
	
	static constexpr uchar SHAPE = 178, SHAPE_AFTER_FREEZE = 219;
	Point pos;
	uchar shape;
	ushort shapeNum;
	array<array<ushort, ROWS>, COLUMNS > figure = {};

private:
	void assign(const Block& _block);
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

	Block() : Block(Point{0, 0}) {}
	Block(const Point& _pos);
	Block(const Point& _pos, const ushort& _shapeNum);
	Block(const Block& _block) { *this = _block; }
	Block& operator=(const Block& b);
	virtual ~Block() = default;
	friend std::ostream& operator<<(std::ostream& out, const Block& _block) { _block.drawBlock(); return out; }
	Block& operator*() { return *this; }
	Block* operator->() { return this; }
	void createNewBlock();
	void drawBlock() const;
	const uchar& getShape() const { return shape; }
	void cleanBlock();
	void setFigure();
	void cleanPrint() const;
	void clockwiseRotate();
	void counterClockwiseRotate();
	void moveLeft();
	void moveRight();
	void moveDown();
	static void changeColorsMode();
	bool isColEmpty(const ushort& col)const;
	size_t getLowestRow()const;
	void setBlockFromFile(const ushort& _shapeNum);
};

class Bomb : public Block
{
	static constexpr  uchar BOMB = 149;
	static constexpr size_t EXPLOSION_RANGE = 4;

	friend class Board;

public:
	Bomb(const uchar& _shape = BOMB) : Bomb({ 0,0 }, _shape) { shapeNum = Block::B; }
	Bomb(const Point& _pos) :Bomb({ _pos }, BOMB) {}
	Bomb(const Point& _pos, const uchar& _shape);
	~Bomb()override = default;
	Bomb& operator=(const Bomb& _bomb)
	{
		if (this != &_bomb)
			Block::operator=(_bomb);
		return *this;
	}
};

#endif
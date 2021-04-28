/***************************************
	Header file for class "Box".
***************************************/
#ifndef _BOX_H_
#define _BOX_H_

#include "Public_const_and_structs.h"
#include "Block.h"
#include "Board.h"
#include "Point.h"

class Box
{
	enum Constants { LENGTH = 8, WIDTH = 8, NUM_OF_BLOCKS = 2 };
	Point pos;
	Board box;
	array<Block, NUM_OF_BLOCKS> blocks;

	friend class Player;
	friend class Game;

private:
	void setBlocks();
	void drawBox() const;
public:
	Box() : Box({0, 0}) {}
	Box(const Point& _pos);
	~Box() = default;
	friend std::ostream& operator<<(std::ostream& out, const Box& _box) { _box.drawBox(); return out; }
	void clearBox();
	void setBoxPosition(const Point& _pos) { pos = _pos; }
};

#endif

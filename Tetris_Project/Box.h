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
	Point pos;
	Board box;
	array<Block,BLOCKS_IN_BOX> blocks;
	
	friend class Player;


private:
	void setBlocks();
	void drawBox()const;
public:
	Box() : Box({ 0,0 }) {}
	Box(const Point& _pos);
	~Box() = default;
	friend ostream& operator<<(ostream& out, const Box& _box) { _box.drawBox(); return out; }
	void clearBox();
};

#endif


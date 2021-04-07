/***************************************
	Header file for class "Box".
***************************************/
#ifndef _BOX_H_
#define _BOX_H_

#include <iostream>

#include "Block.h"
#include "Board.h"
#include "Point.h"
#include "Public const and structs.h"

using namespace std;

struct Box
{
	Point pos;
	Board box;
	array<Block,BLOCKS_IN_BOX> blocks;

private:
	void setBlocks();
public:
	Box() : Box({ 0,0 }) {}
	Box(const Point& _pos);
	~Box() = default;
	void drawBox()const;
	void clearBox();
};

#endif


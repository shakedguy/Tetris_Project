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
	Block blocks[2];

private:
	void drawWalls(int x, int y);
	void setBricks();
public:
	Box() : Box({ 0,0 }) {}
	Box(Point _pos);
	~Box() = default;
	void setPos(int x, int y) { setPos({ x,y }); }
	void setPos(Point _pos) { pos = _pos; }
	void drawBox();
};

#endif


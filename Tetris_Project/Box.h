/***************************************
	Header file for class "Box".
***************************************/
#ifndef _BOX_H_
#define _BOX_H_

#include <iostream>

#include "Block.h"
#include "Point.h"
#include "Public const and structs.h"

using namespace std;

struct Box
{
	Point pos;
	Point box[BOX_WIDTH][BOX_LENGTH];
	Block blocks[3];

private:
	void drawWalls(int x, int y);
	void setBricks();
public:
	Box() : Box({ 0,0 }) {}
	Box(Point _pos);

	void drawBox();
};

#endif


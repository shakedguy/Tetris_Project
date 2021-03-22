/***************************************
	Header file for class "Point".
***************************************/
#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "Public const and structs.h"

using namespace std;

class Point
{
	int x, y;
	enum { UP, DOWN, LEFT, RIGHT };
public:
	Point(int _x = 0, int _y = 0):  x(_x), y(_y) {} 
	void draw(char c);
	void move(int direction);
	void setPos(int _x, int _y);
	int getX() { return x; }
	int getY() { return y; }
};

#endif
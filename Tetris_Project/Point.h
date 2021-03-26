/***************************************
	Header file for class "Point".
***************************************/
#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"
#include "Public const and structs.h"

using namespace std;

class Point
{
	enum { UP, DOWN, LEFT, RIGHT };
	int x, y;
	char shape;

public:
	Point() : Point(0, 0, EMPTY_CELL) {}
	Point(int _x, int _y) : Point(_x, _y, EMPTY_CELL) {}
	Point(int _x, int _y, char _shape) : x(_x), y(_y), shape(_shape) {}
	Point(const Point& _point) : x(_point.x), y(_point.y), shape(_point.shape) {}
	void draw() { gotoxy(x, y); cout << shape << endl; }
	void draw(char ch);
	void move(int direction);
	void setPos(int _x, int _y) { x = _x; y = _y; }
	void setShape(char _shape) { shape = _shape; }
	char getShape() { return shape; }
	int getX() { return x; }
	int getY() { return y; }
};

#endif
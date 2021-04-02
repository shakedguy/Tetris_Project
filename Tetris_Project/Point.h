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
	int x, y;
	char shape;

public:
	Point() : Point(0, 0, EMPTY_CELL) {}
	Point(int _x, int _y) : Point(_x, _y, EMPTY_CELL) {}
	Point(int _x, int _y, char _shape) : x(_x), y(_y), shape(_shape) {}
	Point(const Point& _point) : x(_point.x), y(_point.y), shape(_point.shape) {}
	Point& operator=(const Point& p);
	~Point() = default;
	void draw() const { gotoxy(x, y); cout << shape << endl; }
	void draw(char ch);
	void move(int direction);
	void setPos(int _x, int _y) { x = _x; y = _y; }
	void setPos(Point& _p) { x = _p.getX(); y = _p.getY(); }
	void setShape(char _shape) { shape = _shape; }
	char getShape()	const { return shape; }
	const int& getX() const { return x; }
	const int& getY() const { return y; }
};

#endif
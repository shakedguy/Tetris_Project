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
	uchar shape;

public:
	Point() : Point(0, 0, EMPTY_CELL) {}
	Point(int _x, int _y) : Point(_x, _y, EMPTY_CELL) {}
	Point(int _x, int _y, uchar _shape) : x(_x), y(_y), shape(_shape) {}
	Point(const Point& _point) : x(_point.x), y(_point.y), shape(_point.shape) {}
	Point& operator=(const Point& p);
	~Point() = default;
	void draw() const { gotoxy(x, y); cout << shape << endl; }
	void draw(uchar ch);
	void move(int direction);
	void setShape(const char& _shape) { shape = _shape; }
	uchar getShape()	const { return shape; }
	const int& getX() const { return x; }
	const int& getY() const { return y; }
};

#endif
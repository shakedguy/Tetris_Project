/***************************************
	Header file for class "Point".
***************************************/
#ifndef _POINT_H_
#define _POINT_H_

#include "Public_const_and_structs.h"

class Point
{
	enum Moves { UP = 6, DOWN, LEFT, RIGHT };

	int x, y;
	uchar shape;

private:
	void draw() const { gotoxy(x, y); cout << shape << endl; }
	void assign(const Point& _point) { x = _point.x; y = _point.y; shape = _point.shape; }

public:
	Point() : Point(0, 0, EMPTY_CELL) {}
	Point(int _x, int _y) : Point(_x, _y, EMPTY_CELL) {}
	Point(int _x, int _y, uchar _shape) : x(_x), y(_y), shape(_shape) {}
	Point(const Point& _point) { x = _point.x; y = _point.y; shape = _point.shape; }
	~Point() = default;
	Point& operator=(const Point& _point);
	Point& operator++(int) { y++; return *this; }
	Point& operator+=(const int& _y) { y += _y; return *this; }
	Point& operator--(int) { y--; return *this; }
	Point& operator-=(const int& _y) { y -= _y; return *this; }
	Point& operator>>=(const int& _x) { x += _x; return *this; }
	Point& operator<<=(const int& _x) { x -= _x; return *this; }
	friend std::ostream& operator<<(std::ostream& out, const Point& _point) { _point.draw(); return out; }
	void draw(uchar ch)const;
	void move(int direction);
	int compareY(const Point& _point)const;
	int compareX(const Point& _point)const;
	void setShape(const char& _shape) { shape = _shape; }
	uchar getShape() const { return shape; }
	const int& getX() const { return x; }
	const int& getY() const { return y; }
};

#endif

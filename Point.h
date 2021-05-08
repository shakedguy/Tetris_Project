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
	Color color;

	friend class Board;
	friend class Player;
	friend class ComputerPlayer;
	friend class HumanPlayer;
	friend class Menu;
	friend class Game;
	friend class Block;


private:
	void draw()const; 
	void assign(const Point& _point) { x = _point.x; y = _point.y; shape = _point.shape; color = _point.color; }

public:
	Point() : Point(0, 0, EMPTY_CELL) {}
	Point(int _x, int _y) : Point(_x, _y, EMPTY_CELL) {}
	Point(size_t _x, size_t _y) : Point(static_cast<int>(_x), static_cast<int>(_y), EMPTY_CELL) {}
	Point(const int& _x, const int& _y, const uchar& _shape, const Color& _color = WHITE); 
	Point(const Point& _point) { x = _point.x; y = _point.y; shape = _point.shape; color = _point.color; }
	~Point() = default;
	Point& operator=(const Point& _point);
	Point& operator++(int) { y++; return *this; }
	Point& operator+=(const int& _y) { y += _y; return *this; }
	Point& operator--(int) { y--; return *this; }
	Point& operator-=(const int& _y) { y -= _y; return *this; }
	Point& operator>>=(const int& _x) { x += _x; return *this; }
	Point& operator<<=(const int& _x) { x -= _x; return *this; }
	bool operator==(const Point& position)const { return (x == position.x && y == position.y) ? true : false; }
	friend std::ostream& operator<<(std::ostream& out, const Point& _point) { _point.draw(); return out; }
	void draw(const uchar& ch)const;
	void draw(const Color& _color)const;
	void move(int direction);
	int compareY(const Point& _point)const;
	int compareX(const Point& _point)const;
	uchar getShape() const { return shape; }
	void setShape(const uchar& _shape) { shape = _shape; }
	const int& getX() const { return x; }
	const int& getY() const { return y; }
	void setX(const int& _x) { x = _x; }
	void setY(const int& _y) { y = _y; }
	void setXY(const int& _x, const int& _y) { x = _x; y = _y; }
	void setShapeAndColor(const uchar& _shape, const Color& _color) { shape = _shape; color = _color; }
};

#endif

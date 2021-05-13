/***************************************
	Header file for class "Point".
***************************************/
#ifndef _POINT_H_
#define _POINT_H_

#include "Public_const_and_structs.h"



class Coordinate
{
	friend class Board;
	friend class Player;
	friend class Box;
protected:
	int x, y;
	
	void assign(const Coordinate& _Index) { x = _Index.x; y = _Index.y; }

public:
	Coordinate() : Coordinate(0, 0) {}
	Coordinate(const int& _x, const int& _y) :x(_x), y(_y) {}
	Coordinate(const size_t& _x, const size_t& _y) : Coordinate(static_cast<int>(_x), static_cast<int>(_y)) {}
	Coordinate(const size_t& _x, const int& _y) : Coordinate(static_cast<int>(_x), static_cast<int>(_y)) {}
	Coordinate(const int& _x, const size_t& _y) : Coordinate(static_cast<int>(_x), static_cast<int>(_y)) {}
	Coordinate(const Coordinate& _Index) { *this = _Index; }
	Coordinate(const int& _x, const int& _y, const uchar& _shape, const Color& _color = WHITE);
	virtual ~Coordinate() = default;
	virtual Coordinate& operator*() { return *this; }
	virtual Coordinate* operator->() { return this; }
	virtual Coordinate& operator=(const Coordinate& _point) { assign(_point); return *this; }
	virtual Coordinate& operator++() { *this += 1; return *this; }
	virtual Coordinate operator++(int) { Coordinate p = *this; *this += 1; return p; }
	virtual Coordinate& operator+=(const int& _y) { y += _y; return *this; }
	virtual Coordinate& operator--() { *this -= 1; return *this; }
	virtual Coordinate operator--(int) { Coordinate p = *this; *this -= 1; return p; }
	virtual Coordinate& operator-=(const int& _y) { y -= _y; return *this; }
	virtual Coordinate& operator>>=(const int& _x) { x += _x; return *this; }
	virtual Coordinate& operator<<=(const int& _x) { x -= _x; return *this; }
	virtual bool operator==(const Coordinate& position)const { return (x == position.x && y == position.y) ? true : false; }
	virtual bool operator!=(const Coordinate& position)const { return (!(position == *this)); }
	virtual int compareY(const Coordinate& _point)const;
	virtual int compareX(const Coordinate& _point)const;
	virtual const int& getX() const { return x; }
	virtual const int& getY() const { return y; }
	virtual void setX(const int& _x) { x = _x; }
	virtual void setY(const int& _y) { y = _y; }
	virtual void setXY(const int& _x, const int& _y) { x = _x; y = _y; }
	virtual void draw(const uchar& ch)const;
	virtual void draw(const uchar& ch, const Color& _color)const;

};


class Point : public Coordinate
{
	enum Moves { UP = 6, DOWN, LEFT, RIGHT };
	uchar shape;
	Color color;

	friend class Board;
	friend class Player;
	friend class Box;

private:
	void draw()const; 
	void assign(const Point& _point);

public:
	Point() : Point(0, 0, EMPTY_CELL) {}
	Point(const int& _x, const int& _y) : Point(_x, _y, EMPTY_CELL) {}
	Point(const size_t& _x, const size_t& _y) : Point(static_cast<int>(_x), static_cast<int>(_y), EMPTY_CELL) {}
	Point(const size_t& _x, const int& _y) : Point(static_cast<int>(_x), static_cast<int>(_y), EMPTY_CELL) {}
	Point(const int& _x, const size_t& _y) : Point(static_cast<int>(_x), static_cast<int>(_y), EMPTY_CELL) {}
	Point(const Point& _point) { *this = _point; }
	Point(const int& _x, const int& _y, const uchar& _shape, const Color& _color = WHITE);
	~Point()override = default;
	Point& operator*()override { return *this; }
	Point* operator->()override { return this; }
	Point& operator=(const Point& _point);
	bool operator==(const Point& position)const;
	bool operator!=(const Point& position)const { return (!(position == *this)); }
	friend std::ostream& operator<<(std::ostream& out, const Point& _point) { _point.draw(); return out; }
	void draw(const Color& _color)const;
	void move(const int& direction);
	const uchar& getShape() const { return shape; }
	void setShape(const uchar& _shape) { shape = _shape; }
	void setShapeAndColor(const uchar& _shape, const Color& _color) { shape = _shape; color = _color; }
};

#endif

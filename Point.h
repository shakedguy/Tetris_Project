/***************************************
	Header file for class "Point".
***************************************/
#ifndef _POINT_H_
#define _POINT_H_

#include "Public_const_and_structs.h"



class Point
{
	friend class Board;

protected:
	int x, y;
	
	void assign(const Point& _Index) { x = _Index.x; y = _Index.y; }

public:
	Point() : Point(0, 0) {}
	Point(const int& _x, const int& _y) :x(_x), y(_y) {}
	Point(const size_t& _x, const size_t& _y) : Point(static_cast<int>(_x), static_cast<int>(_y)) {}
	Point(const size_t& _x, const int& _y) : Point(static_cast<int>(_x), static_cast<int>(_y)) {}
	Point(const int& _x, const size_t& _y) : Point(static_cast<int>(_x), static_cast<int>(_y)) {}
	Point(const Point& _Index) { *this = _Index; }
	Point(const int& _x, const int& _y, const uchar& _shape, const Color& _color = WHITE);
	virtual ~Point() = default;
	virtual Point& operator*() { return *this; }
	virtual Point* operator->() { return this; }
	virtual Point& operator=(const Point& _point) { assign(_point); return *this; }
	virtual Point& operator++() { *this += 1; return *this; }
	virtual Point operator++(int) { Point p = *this; *this += 1; return p; }
	virtual Point& operator+=(const int& _y) { y += _y; return *this; }
	virtual Point& operator--() { *this -= 1; return *this; }
	virtual Point operator--(int) { Point p = *this; *this -= 1; return p; }
	virtual Point& operator-=(const int& _y) { y -= _y; return *this; }
	virtual Point& operator>>=(const int& _x) { x += _x; return *this; }
	virtual Point& operator<<=(const int& _x) { x -= _x; return *this; }
	virtual bool operator==(const Point& position)const { return (x == position.x && y == position.y) ? true : false; }
	virtual bool operator!=(const Point& position)const { return (!(position == *this)); }
	virtual int compareY(const Point& _point)const;
	virtual int compareX(const Point& _point)const;
	virtual const int& getX() const { return x; }
	virtual const int& getY() const { return y; }
	void setX(const int& _x) { x = _x; }
	void setY(const int& _y) { y = _y; }
	void setXY(const int& _x, const int& _y) { x = _x; y = _y; }
	virtual void draw(const uchar& ch)const;
	virtual void draw(const uchar& ch, const Color& _color)const;

};


class Cell : public Point
{
	enum Moves { UP = 6, DOWN, LEFT, RIGHT };
	uchar shape;
	Color color;

	friend class Board;

private:
	void draw()const; 
	void assign(const Cell& _cell);

public:
	Cell() : Cell(0, 0, EMPTY_CELL) {}
	Cell(const int& _x, const int& _y) : Cell(_x, _y, EMPTY_CELL) {}
	Cell(const size_t& _x, const size_t& _y) : Cell(static_cast<int>(_x), static_cast<int>(_y), EMPTY_CELL) {}
	Cell(const size_t& _x, const int& _y) : Cell(static_cast<int>(_x), static_cast<int>(_y), EMPTY_CELL) {}
	Cell(const int& _x, const size_t& _y) : Cell(static_cast<int>(_x), static_cast<int>(_y), EMPTY_CELL) {}
	Cell(const Cell& _cell) { *this = _cell; }
	Cell(const int& _x, const int& _y, const uchar& _shape, const Color& _color = WHITE);
	~Cell()override = default;
	Cell& operator*()override { return *this; }
	Cell* operator->()override { return this; }
	Cell& operator=(const Cell& _cell);
	bool operator==(const Cell& cell)const;
	bool operator!=(const Cell& position)const { return (!(position == *this)); }
	friend std::ostream& operator<<(std::ostream& out, const Cell& _cell) { _cell.draw(); return out; }
	const Point& getPoint()const { return { x,y }; }
	void draw(const Color& _color)const;
	void move(const int& direction);
	const uchar& getShape() const { return shape; }
	void setShape(const uchar& _shape) { shape = _shape; }
	void setShapeAndColor(const uchar& _shape, const Color& _color) { shape = _shape; color = _color; }
};

#endif

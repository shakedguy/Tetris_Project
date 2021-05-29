/***************************************
	Header file for class "Point".
***************************************/
#ifndef _POINT_H_
#define _POINT_H_

#include "Public_const_and_structs.h"

class Point
{

	enum Shift { UP = 6, DOWN, LEFT, RIGHT };

protected:

	int x, y;
	
	void assign(const Point& _Index) { x = _Index.x; y = _Index.y; }
	void assign(const int& _x, const int& _y) { x = _x; y = _y; }
	friend class Board;
	friend class File_Handler;

public:
	Point() : Point(0, 0) {}
	template<class T, class G>
		Point(const T& _x, const G& _y) :x(static_cast<int>(_x)), y(static_cast<int>(_y)) {}
	Point(const Point& _Index) { x = _Index.x; y = _Index.y; }
	virtual ~Point() = default;
	virtual Point& operator*() { return *this; }
	virtual Point* operator->() { return this; }
	virtual Point& operator=(const Point& _point);
	virtual Point& operator++() { *this += 1; return *this; }
	virtual Point operator++(int) { Point p = *this; *this += 1; return p; }
	virtual Point& operator+=(const int& _y) { y += _y; return *this; }
	virtual Point& operator--() { *this -= 1; return *this; }
	virtual Point operator--(int) { Point p = *this; *this -= 1; return p; }
	virtual Point& operator-=(const int& _y) { y -= _y; return *this; }
	virtual Point& operator>>=(const int& _x) { x += _x; return *this; }
	virtual Point& operator<<=(const int& _x) { x -= _x; return *this; }
	virtual bool operator==(const Point& position)const
		{ return (x == position.x && y == position.y) ? true : false; }
	virtual bool operator!=(const Point& position)const { return (!(position == *this)); }
	virtual int compareY(const Point& _point)const;
	virtual int compareX(const Point& _point)const;
	const int& getX() const { return x; }
	const int& getY() const { return y; }
	template<class T>
	void setX(const T& _x) { x = static_cast<int>(_x); }
	template<class T>
	void setY(const T& _y) { y = static_cast<int>(_y); }
	template<class T>
	void setX(const T* _x) { x = static_cast<int>(*_x); }
	template<class T>
	void setY(const int* _y) { y = static_cast<int>(*_y); }
	template<class T>
		void shift(const T& direction);
	template<class T, class G>
	void setXY(const T& _x, const G& _y) { x = static_cast<int>(_x); y = static_cast<int>(_y); }
	void draw(const uchar& ch)const;
	void draw(const uchar& ch, const Color& _color)const;

};

class Cell : public Point
{
	uchar shape;
	Color color;

	friend class Board;
	friend class File_Handler;

private:

	void draw()const; 
	void assign(const Cell& _cell);

public:
	Cell() : Point(0, 0), shape(EMPTY_CELL), color(WHITE) {}
	template<class T, class G>
	Cell::Cell(const T& _x, const G& _y, const uchar& _shape = EMPTY_CELL,
		const Color& _color = WHITE) : Point(_x, _y), shape(_shape), color(_color) {}
	Cell(const Cell& _cell) { assign(_cell); }
	~Cell()override = default;
	Cell& operator*()override { return *this; }
	Cell* operator->()override { return this; }
	Cell& operator=(const Cell& _cell);
	bool operator==(const Cell& cell)const;
	bool operator!=(const Cell& position)const { return (!(position == *this)); }
	friend std::ostream& operator<<(std::ostream& out, const Cell& _cell)
		{ _cell.draw(); return out; }
	const Point& getPoint()const { return { x,y }; }
	void draw(const Color& _color)const;
	const uchar& getShape() const { return shape; }
	void setShape(const uchar& _shape) { shape = _shape; }
	void setShapeAndColor(const uchar& _shape, const Color& _color)
		{ shape = _shape; color = _color; }
};

#endif

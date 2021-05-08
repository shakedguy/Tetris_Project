/***************************************
	cpp file for class "Point".
***************************************/
#include "Point.h"
#include "io_utils.h"

Point::Point(const int& _x, const int& _y, const uchar& _shape, const Color& _color) :
	x(_x), y(_y), shape(_shape), color(_color) {}

Point& Point::operator=(const Point& _point) {
	if (&_point != this) {
		assign(_point);
	}
	return *this;
}


void Point::move(int direction) {

	switch (direction) {
	case UP: // UP
		--y;
		break;
	case DOWN: // DOWN
		++y;
		break;
	case LEFT: // MOVE_LEFT
		--x;
		break;
	case RIGHT: // MOVE_RIGHT
		++x;
		break;

		default:
			break;
	}
}

void Point::draw(const uchar& ch)const
{
	gotoxy(x, y);
	cout << ch << endl;
}

int Point::compareX(const Point& _point)const
{
	if (this->x == _point.x)
		return 0;
	return (this->x < _point.x) ? 1 : -1;
}

int Point::compareY(const Point& _point)const
{
	if (this->y == _point.y)
		return 0;
	return (this->y < _point.y) ? 1 : -1;
}

void Point::draw() const
{
	setTextColor(color);
	gotoxy(x, y);
     cout << shape;
	setTextColor(WHITE);
}

void Point::draw(const Color& _color) const
{
	setTextColor(_color);
	gotoxy(x, y);
	cout << shape;
	setTextColor(WHITE);
}




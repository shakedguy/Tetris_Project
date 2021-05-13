/***************************************
	cpp file for class "Coordinate".
***************************************/
#include "Point.h"
#include "io_utils.h"


void Coordinate::draw(const uchar& ch)const
{
	gotoxy(x, y);
	cout << ch << endl;
}

void Coordinate::draw(const uchar& ch, const Color& _color) const
{
	setTextColor(_color);
	draw(ch);
	setTextColor(WHITE);
}

int Coordinate::compareX(const Coordinate& _point)const
{
	if (this->x == _point.x)
		return 0;
	return (this->x < _point.x) ? 1 : -1;
}

int Coordinate::compareY(const Coordinate& _point)const
{
	if (this->y == _point.y)
		return 0;
	return (this->y < _point.y) ? 1 : -1;
}

Point::Point(const int& _x, const int& _y, const uchar& _shape, const Color& _color) :
	shape(_shape), color(_color) {}

void Point::assign(const Point& _point)
{
	Coordinate::assign({ _point.getX(),_point.getY() });
	shape = _point.shape; color = _point.color;
}


bool Point::operator==(const Point& position) const
{
	return (Coordinate{ x,y } == Coordinate{ position.x,position.y } &&
		shape == position.shape && color == position.color) ? true : false;
}


Point& Point::operator=(const Point& _point) {
	if (&_point != this)
		assign(_point);
	return *this;
}

void Point::move(const int& direction) {

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



void Point::draw() const
{
	Coordinate::draw(shape,color);
}

void Point::draw(const Color& _color) const
{
	Coordinate::draw(shape, _color);
}




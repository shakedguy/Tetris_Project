/***************************************
	cpp file for class "Point".
***************************************/
#include "Point.h"
#include "io_utils.h"


void Point::draw(const uchar& ch)const
{
	gotoxy(x, y);
	cout << ch << endl;
}

void Point::draw(const uchar& ch, const Color& _color) const
{
	setTextColor(_color);
	draw(ch);
	setTextColor(WHITE);
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

Cell::Cell(const int& _x, const int& _y, const uchar& _shape, const Color& _color) :
	shape(_shape), color(_color) {}

void Cell::assign(const Cell& _cell)
{
	Point::assign({ _cell.getX(),_cell.getY() });
	shape = _cell.shape; color = _cell.color;
}


bool Cell::operator==(const Cell& cell) const
{
	return (Point{ x,y } == Point{ cell.x,cell.y } &&
		shape == cell.shape && color == cell.color) ? true : false;
}


Cell& Cell::operator=(const Cell& _cell) {
	if (&_cell != this)
		assign(_cell);
	return *this;
}

void Cell::move(const int& direction) {

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



void Cell::draw() const
{
	Point::draw(shape,color);
}

void Cell::draw(const Color& _color) const
{
	Point::draw(shape, _color);
}




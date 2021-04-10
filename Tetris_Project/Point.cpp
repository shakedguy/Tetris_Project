/***************************************
	cpp file for class "Point".
***************************************/
#include "Point.h"
#include "io_utils.h"

Point& Point::operator=(const Point& _point)
{
	if(&_point!=this)
	{
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
	}
}

void Point::draw(uchar ch) {
	gotoxy(x, y);
	cout << ch << endl;
}
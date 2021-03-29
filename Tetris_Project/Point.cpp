/***************************************
	cpp file for class "Point".
***************************************/
#include "Point.h"
#include "io_utils.h"

Point& Point::operator=(const Point& p)
{
	if(&p!=this)
	{
		x = p.x;
		y = p.y;
		shape = p.shape;
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
	case LEFT: // LEFT
		--x;
		break;
	case RIGHT: // RIGHT
		++x;
		break;
	}
}

void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch << endl;
}
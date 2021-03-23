/***************************************
	cpp file for class "Point".
***************************************/
#include "Point.h"
#include "io_utils.h"

void Point::move(int dir) {

	switch (dir) {
	case UP: // UP
		--y;
		if (y < 1) {
			y = 24;
		}
		break;
	case DOWN: // DOWN
		++y;
		if (y > 24) {
			y = 1;
		}
		break;
	case LEFT: // LEFT
		--x;
		if (x < 1) {
			x = 79;
		}
		break;
	case RIGHT: // RIGHT
		++x;
		if (x > 79) {
			x = 1;
		}
		break;
	}
}

void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch << endl;
}
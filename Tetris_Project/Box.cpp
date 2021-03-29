#include "Box.h"

Box::Box(Point _pos) : pos(_pos) {

	for (int x = 0; x < BOX_WIDTH; x++)
	{
		for (int y = 0; y < BOX_LENGTH; y++)
		{
			box[x][y].setPos(pos.getX() + x, pos.getY() + y);
			drawWalls(x, y);
		}
	}
	setBricks();
	drawBox();	
}

void Box::setBricks() {

	int y = 2;
	for (int i = 0; i < 3; i++) {

		blocks[i].setPos({ (pos.getX() + 4), (pos.getY() + y) });
		blocks[i].set_Brick();
		y += 3;
	}
}
void Box::drawWalls(int x, int y) {

	if (y == 0 || y == BOX_LENGTH - 1)
	{
		if (y == 0 && x == 0)
			box[x][y].setShape(UP_LEFT);
		else if (y == 0 && x == BOX_WIDTH - 1)
			box[x][y].setShape(UP_RIGHT);
		else if (x > 0 && x < BOX_WIDTH - 1)
			box[x][y].setShape(FLOOR);
		else if (y == BOX_LENGTH - 1 && x == 0)
			box[x][y].setShape(DOWN_LEFT);
		else if (y == BOX_LENGTH - 1 && x == BOX_WIDTH - 1)
			box[x][y].setShape(DOWN_RIGHT);

	}
	if ((x == 0 || x == BOX_WIDTH - 1) && (y != 0 && (y != BOX_LENGTH - 1)))
		box[x][y].setShape(WALL);
}
void Box::drawBox()
{
	for (int i = 0; i < BOX_WIDTH; i++)
	{
		for (int j = 0; j < BOX_LENGTH; j++)
		{
			box[i][j].draw();
		}
	}
	for (int i = 0; i < 3; i++)
		blocks[i].printBrick();
}


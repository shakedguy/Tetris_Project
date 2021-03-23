#include "Box.h"


void Box::drawBox()
{
	for (int i = 0; i < BOX_WIDTH; i++)
	{
		for (int j = 0; j < BOX_LENGTH; j++)
		{
			drawWalls(i, j);
		}
	}
	for (int i = 0; i < 3; i++)
		bricks[i].drawBrick();
}

void Box::drawWalls(int x, int y)
{
	box[x][y].setPos(pos.getX() + x, pos.getY() + y);
	if (y == 0 || y == BOX_LENGTH - 1)
	{
		if (y == 0 && x == 0)
			box[x][y].draw(UP_LEFT);
		else if (y == 0 && x == BOX_WIDTH - 1)
			box[x][y].draw(UP_RIGHT);
		else if (x > 0 && x < BOX_WIDTH - 1)
			box[x][y].draw(FLOOR);
		else if (y == BOX_LENGTH - 1 && x == 0)
			box[x][y].draw(DOWN_LEFT);
		else if (y == BOX_LENGTH - 1 && x == BOX_WIDTH - 1)
			box[x][y].draw(DOWN_RIGHT);

	}
	if ((x == 0 || x == BOX_WIDTH - 1) && (y != 0 && (y != BOX_LENGTH - 1)))
		box[x][y].draw(WALL);
}
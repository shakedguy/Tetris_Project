#include "Box.h"

Box::Box(Point _pos) : pos(_pos)
{
	for (int x = 0; x < BOX_WIDTH; x++)
		for (int y = 0; y < BOX_LENGTH; y++)
			drawWalls(x, y);
	setBricks();
	drawBox();
}

void Box::setBricks()
{
	int y = 2;
	for (int i = 0; i < 2; i++)
	{
		blocks[i].setPos({(pos.getX() + 4), (pos.getY() + y)});
		y += 5;
	}
}

void Box::drawWalls(int x, int y)
{
	if (y == 0 || y == BOX_LENGTH - 1)
	{
		if (y == 0 && x == 0)
			box[x][y] = UP_LEFT;
		else if (y == 0 && x == BOX_WIDTH - 1)
			box[x][y] = UP_RIGHT;
		else if (x > 0 && x < BOX_WIDTH - 1)
			box[x][y] = FLOOR;
		else if (y == BOX_LENGTH - 1 && x == 0)
			box[x][y] = DOWN_LEFT;
		else if (y == BOX_LENGTH - 1 && x == BOX_WIDTH - 1)
			box[x][y] = DOWN_RIGHT;
	}
	else if ((x == 0 || x == BOX_WIDTH - 1) && (y != 0 && (y != BOX_LENGTH - 1)))
		box[x][y] = WALL;
	else
		box[x][y] = EMPTY_CELL;
}

void Box::drawBox()
{
	for (int i = 0; i < BOX_WIDTH; i++)
	{
		for (int j = 0; j < BOX_LENGTH; j++)
		{
			gotoxy(pos.getX() + i, pos.getY() + j);
			cout << box[i][j];
		}
	}
	for (Block& i : blocks)
		i.drawBlock();
}

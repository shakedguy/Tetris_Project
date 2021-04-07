#include "Box.h"

Box::Box(Point _pos) : pos(_pos), box({ pos }, BOX_LENGTH,BOX_WIDTH)
{
	box.setAllBoundaries();
	setBricks();
}

void Box::setBricks()
{
	int y = 1;
	for (int i = 0; i < 2; i++)
	{
		blocks[i].pos = { (pos.getX() + 2), (pos.getY() + y) };
		y += 4;
	}
}

void Box::drawBox()
{
	gotoxy((box.pos.getX()), box.pos.getY() - 1);
	cout << "Next blocks";
	box.drawBoard();
	for (Block& i : blocks)
		i.drawBlock();
}

void Box::clearBox()
{
	for (Block& i : blocks)
		i.createNewBlock();
}


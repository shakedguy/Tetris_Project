#include "Box.h"

Box::Box(Point _pos) : pos(_pos), box({ pos }, BOX_LENGTH,BOX_WIDTH)
{
	box.setAllBoundaries();
	setBricks();
}

void Box::setBricks()
{
	int y = 0;
	for (int i = 0; i < 2; i++)
	{
		blocks[i].setPos({(pos.getX() + 4), (pos.getY() + y)});
		y += 5;
	}
}

void Box::drawBox()
{
	box.drawBoard();
	for (Block& i : blocks)
		i.drawBlock();
}

void Box::clearBox()
{
	for (Block& i : blocks)
		i.createNewBlock();
}


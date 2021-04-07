﻿#include "Box.h"

Box::Box(const Point& _pos) : pos(_pos), box({ pos }, BOX_LENGTH,BOX_WIDTH)
{
	box.setAllBoundaries();
	setBlocks();
}

void Box::setBlocks()
{
	int y = 1;
	for (Block& block:blocks)
	{
		block.pos = { (pos.getX() + 2), (pos.getY() + y) };
		y += 4;
	}
}

void Box::drawBox()const
{
	gotoxy((box.pos.getX()), box.pos.getY() - 1);
	cout << "Next blocks";
	box.drawBoard();
	for (const Block& i : blocks)
		i.drawBlock();
}

void Box::clearBox()
{
	for (Block& i : blocks)
		i.createNewBlock();
}


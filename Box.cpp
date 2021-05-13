#include "Box.h"

Box::Box(const Coordinate& _pos) {

	pos = _pos;
	setBoxPos(pos);
	resizeBoundaries(LENGTH, WIDTH);
	initialEmptyCells();
	setAllBoundaries();
	setBlocks();
}

Box& Box::operator=(const Box& _box)
{
	if (this != &_box)
	{
		Board::operator=(_box);
		if (blocks.size() == _box.blocks.size())
			for (size_t i = 0; i < blocks.size(); ++i)
				blocks[i] = _box.blocks[i];
	}
	return *this;
}

// Sets locations for blocks in the box
void Box::setBlocks() {
	
	ushort y = 1;
	for (Block& block : blocks) {
		block.pos = {(pos.getX() + 2), (pos.getY() + y)};
		y += 4;
	}
}

void Box::drawBox() const {
	
	gotoxy((pos.getX()), pos.getY() - 1);
	cout << "Next blocks";
	drawBoard();
	for (const Block& i : blocks)
		i.drawBlock();
}

void Box::clearBox()
{
	for (Block& i : blocks)
		i.createNewBlock();
}

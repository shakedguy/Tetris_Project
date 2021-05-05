#include "Box.h"

Box::Box(const Point& _pos) : pos(_pos), box({pos}, LENGTH,WIDTH) {
	
	box.setAllBoundaries();
	setBlocks();
}

Box& Box::operator=(const Box& _box)
{
	if (this != &_box)
	{
		pos = _box.pos;
		box = _box.box;
		if (blocks.size() == _box.blocks.size())
		{
			for (size_t i = 0; i < blocks.size(); ++i)
				blocks[i] = _box.blocks[i];
		}
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
	
	gotoxy((box.pos.getX()), box.pos.getY() - 1);
	cout << "Next blocks";
	cout << box;
	box.drawBoard();
	for (const Block& i : blocks)
		i.drawBlock();
}

void Box::clearBox() {

	for (Block& i : blocks)
		i.createNewBlock();
}

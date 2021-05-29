#include "Box.h"


Box::Box(const Point& _pos) : Board(_pos)
{
	setPos(_pos);
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
			blocks = _box.blocks;
	}
	return *this;
}

// Sets locations for blocks in the box
void Box::setBlocks() {
	
	ushort y = 1;
	for (Block& block : blocks) {
		block.pos = /*Point< size_t, size_t>*/{ 2 + pos.getX(), pos.getY() + y};
		y += 4;
	}
}

void Box::drawBox() const {
	
	gotoxy((pos.getX()), pos.getY() - 1);
	cout << "Next blocks";
	Board::drawBoard();
	for (const Block& i : blocks)
		i.drawBlock();
}

void Box::clearBox()
{
	for (Block& i : blocks)
		i.createNewBlock();
}

void Box::clearScreen()
{
	Board::clearScreen();
	for (Block& block : blocks)
		block.cleanPrint();
}




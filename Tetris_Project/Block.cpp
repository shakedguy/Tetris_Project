#include "Block.h"


Block& Block::operator=(const Block& b)
{
	if(&b!=this)
	{
		for (int i = 0; i < BLOCK_SIZE; i++)
			type[i] = b.type[i];

		pos = b.pos;
		shape = b.shape;
		shapeNum = b.shapeNum;
		color = b.color;
	}
	return *this;
}

Block& Block::createBlock(const Point& pos)
{
	Block b(pos);
	return b;
}





void Block::set_Brick()
{
	switch (shapeNum)
	{
	case 0:
		set_Block0();
		break;
	case 1:
		set_Block1();
		break;
	case 2:
		set_Block2();
		break;
	case 3:
		set_Block3();
		break;
	case 4:
		set_Block4();
		break;
	case 5:
		set_Block5();
		break;
	case 6:
		set_Block6();
		break;

	default:
		break;
	}
}

void Block::set_Block0()
{
	for (int i = 0; i < 4; i++) {

		type[i].setPos(pos.getX() + i, pos.getY());
		type[i].setShape(SHAPE);
	}

}
void Block::set_Block1()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{

			if ((i == 0) || (j == 1)) {

				type[count].setPos(pos.getX() + i, pos.getY() + j);
				type[count++].setShape(SHAPE);
			}
		}
	}
}

void Block::set_Block2()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{

			if ((i == 2) || (j == 1)) {

				type[count].setPos(pos.getX() + i, pos.getY() + j);
				type[count++].setShape(SHAPE);
			}
		}
	}
}
void Block::set_Block3()
{
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++) {

			type[count].setPos(pos.getX() + i, pos.getY() + j);
			type[count++].setShape(SHAPE);
		}
	}
}
void Block::set_Block4()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{

			if ((j == 0 && i > 0) || (j == 1 && i < 2)) {

				type[count].setPos(pos.getX() + i, pos.getY() + j);
				type[count++].setShape(SHAPE);
			}
		}
	}
}
void Block::set_Block5()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{

			if ((i == 1) || (j == 1)) {

				type[count].setPos(pos.getX() + i, pos.getY() + j);
				type[count++].setShape(SHAPE);
			}

		}
	}
}
void Block::set_Block6()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{

			if ((j == 0 && i < 2) || (j == 1 && i > 0)) {

				type[count].setPos(pos.getX() + i, pos.getY() + j);
				type[count++].setShape(SHAPE);
			}

		}
	}
}

void Block::move(int dir)
{
	switch (dir)
	{
	case LEFT:
		move_Left();
		break;
	case RIGHT:
		move_Right();
		break;
	case DOWN:
		move_Down();
	default:
		break;
	}
	printBrick();
}

void Block::move_Left()
{
	for (int i = 0; i < 4; i++) {

		gotoxy(type[i].getX(), type[i].getY());
		cout << ' ';
		type[i].move(LEFT);
	}
}

void Block::move_Right()
{
	for (int i = 0; i < 4; i++) {

		gotoxy(type[i].getX(), type[i].getY());
		cout << ' ';
		type[i].move(RIGHT);
	}
}

void Block::move_Down()
{
	for (int i = 0; i < 4; i++) {

		gotoxy(type[i].getX(), type[i].getY());
		cout << ' ';
		type[i].move(DOWN);
	}
}

void Block::printBrick() {

	for (auto& i : type)
		i.draw();
	gotoxy(0, 0);
}

void Block::cleanBlock()
{
	for (int i = 0; i < 4; i++)
		type[i].setShape(' ');
	printBrick();
}

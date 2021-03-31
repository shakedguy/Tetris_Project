﻿#include "Block.h"

Block::Block(Point _pos) : pos(_pos), color(0), shape(SHAPE)
{
	random_device rnd;
	const uniform_int_distribution<> range(1, 7);
	shapeNum = (range(rnd));
	setFigure();
}

Block& Block::operator=(const Block& b)
{
	//if(&b!=this)
	//{
		for (int i = 0; i < BLOCK_MATRIX; i++)
			for (int j = 0; j < BLOCK_MATRIX; j++)
				figure[i][j] = figure[i][j];

		pos = b.pos;
		shape = b.shape;
		shapeNum = b.shapeNum;
		color = b.color;
	//}
	return *this;
}

void Block::createNewBlock()
{
	cleanBlock();
	random_device rnd;
	const uniform_int_distribution<> range(1, 7);
	shapeNum = (range(rnd));
	setFigure();
}


void Block::setFigure()
{
	switch (shapeNum)
	{
	case 1:
		set_Figure1();
		break;
	case 2:
		set_Figure2();
		break;
	case 3:
		set_Figure3();
		break;
	case 4:
		set_Figure4();
		break;
	case 5:
		set_Figure5();
		break;
	case 6:
		set_Figure6();
		break;
	case 7:
		set_Figure7();
		break;

	default:
		break;
	}
}

void Block::set_Figure1()
{
	for (int i = 0; i < 4; i++) {
		figure[i][2]++;
	}

}
void Block::set_Figure2()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (!(i + j))
				figure[i][j]++;
			else if (j)
				figure[i][j]++;
		}
	}
}

void Block::set_Figure3()
{
	for (int i = 1; i < 4; i++)
		for (int j = 0; j < 2; j++)
			if ((!j && i > 2) || j)
				figure[i][j]++;
}
void Block::set_Figure4()
{
	for (int i = 1; i < 3; i++)
		for (int j = 1; j < 3; j++)
			figure[i][j]++;
}
void Block::set_Figure5()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			if ((j < 1 && i) || (j > 0 && i < 2))
				figure[i][j]++;
}
void Block::set_Figure6()
{
	for (int i = 0; i < 3; i++)
		for (int j = 2; j < 4; j++)
			if ((j < 3 && i == 1) || j > 2)
				figure[i][j]++;
}
void Block::set_Figure7()
{
	for (int i = 0; i < 3; i++)
		for (int j = 2; j < 4; j++)
			if ((j < 3 && i < 2) || (j > 2 && i))
				figure[i][j]++;
}

void Block::move(int dir)
{
	cleanPrint();
	switch (dir)
	{
	case LEFT:
		pos.move(LEFT);
		break;
	case RIGHT:
		pos.move(RIGHT);
		break;
	case DOWN:
		pos.move(DOWN);
		break;
	case UP:
		rotate();
		break;
		
		default:
			pos.move(DOWN);
			break;
	}
	drawBlock();
}

void Block::drawBlock() {

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (figure[i][j])
			{
				gotoxy(pos.getX() + i, pos.getY() + j);
				cout << shape;
				//cout << figure[i][j];
			}	
		}
	}
	gotoxy(0, 0);
}

void Block::cleanBlock()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			figure[i][j] = 0;
}

void Block::cleanPrint()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			gotoxy(pos.getX() + i, pos.getY() + j);
			cout << EMPTY_CELL;
		}	
	}
}

void Block::rotate()
{
	transpose_Matrix();
	reverse_Matrix();
}

void Block::copyFigure(const Block& b)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			figure[i][j] = b.figure[i][j];
		}
	}
}


void Block::transpose_Matrix()
{
	for (int i = 0; i < BLOCK_MATRIX; i++)
		for (int j = i + 1; j < BLOCK_MATRIX; j++)
			swap(figure[i][j], figure[j][i]);
}

void Block::reverse_Matrix()
{
	for (int i = 0; i < BLOCK_MATRIX; i++) {

		int start = 0;
		int end = BLOCK_MATRIX - 1;


		while (start < end) {
			swap(figure[i][start], figure[i][end]);
			start++;
			end--;
		}
	}
}




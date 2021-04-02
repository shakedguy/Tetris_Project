#include "Block.h"

Block::Block(Point _pos) : pos(_pos), color(0), shape(SHAPE)
{
	random_device rnd;
	const uniform_int_distribution<> range(1, 7);
	shapeNum = (range(rnd));
	setFigure();
}

Block& Block::operator=(const Block& b)
{
	if(&b!=this)
	{
		for (int i = 0; i < BLOCK_MATRIX; i++)
			for (int j = 0; j < BLOCK_MATRIX; j++)
				figure[i][j] = figure[i][j];

		pos = b.pos;
		shape = b.shape;
		shapeNum = b.shapeNum;
		color = b.color;
	}
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
	for (int i = 0; i < 4; i++)
		figure[i][BLOCK_MATRIX - 1]++;
}
void Block::set_Figure2()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 2; j < 4; j++)
		{
			if ((i + j) < 3)
				figure[i][j]++;
			else if (j > 2)
				figure[i][j]++;
		}
	}
}

void Block::set_Figure3()
{
	for (int i = 0; i < 3; i++)
		for (int j = 2; j < 4; j++)
			if ((j == 2 && i > 1) || j != 2)
				figure[i][j]++;
}
void Block::set_Figure4()
{
	for (int i = 0; i < 2; i++)
		for (int j = 2; j < 4; j++)
			figure[i][j]++;
}
void Block::set_Figure5()
{
	for (int i = 0; i < 3; i++)
		for (int j = 2; j < 4; j++)
			if ((j == 2 && i) || (j != 2 && i < 2))
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

void Block::arrangeMatrix()
{
	if (isEmptyRow(BLOCK_MATRIX-1))
	{
		moveFifureInMatrix();
		arrangeMatrix();
	}
	
}

void Block::moveFifureInMatrix()
{
	for (int i = 0; i < BLOCK_MATRIX; i++)
		for (int j = BLOCK_MATRIX - 1; j > 0; j--)
			swap(figure[i][j], figure[i][j - 1]);

	for (int i = 0; i < BLOCK_MATRIX; i++)
		figure[i][0] = 0;
}


bool Block::isEmptyRow(const unsigned& row)
{
	for (int i = 0; i < BLOCK_MATRIX; i++)
		if (figure[i][row])
			return false;
	return true;
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
	case CLOCKWISE:
		clockwiseRotate();
		break;
	case COUNTER_CLOCKWISE:
		counterClockwiseRotate();
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

void Block::clockwiseRotate()
{
	transpose_Matrix();
	reverseColumns();
	arrangeMatrix();
}

void Block::counterClockwiseRotate()
{
	transpose_Matrix();
	reverseRows();
	arrangeMatrix();
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

void Block::reverseColumns()
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
void Block::reverseRows()
{
	for (int i = 0; i < BLOCK_MATRIX; i++) {

		int start = 0;
		int end = BLOCK_MATRIX - 1;


		while (start < end) {
			swap(figure[start][i], figure[end][i]);
			start++;
			end--;
		}
	}
}




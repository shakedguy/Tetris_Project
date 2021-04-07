#include "Block.h"

Block::Block(Point _pos) : pos(_pos), shape(SHAPE)
{
	random_device rnd;
	const uniform_int_distribution<> shapeRange(1, 7);
	const uniform_int_distribution<> colorRange(1, 14);
	shapeNum = (shapeRange(rnd));
	color = static_cast<Color>(colorRange(rnd));
	cleanBlock();
	setFigure();
}

Block& Block::operator=(const Block& b)
{
	if(&b!=this)
	{
		cleanBlock();
		for (int i = 0; i < figure.size(); i++)
			for (int j = 0; j < figure[i].size(); j++)
				figure[i][j] = b.figure[i][j];

		pos = b.pos;
		shape = b.shape;
		color = b.color;
		shapeNum = b.shapeNum;
		color = b.color;
	}
	return *this;
}

void Block::createNewBlock()
{
	cleanBlock();
	random_device rnd;
	const uniform_int_distribution<> shapeRange(1, 7);
	const uniform_int_distribution<> colorRange(1, 14);
	shapeNum = (shapeRange(rnd));
	color = static_cast<Color>(colorRange(rnd));
	setFigure();
}


/********** Set figures ***********/
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
	for (int i = 0; i < figure.size(); i++)
		figure[i][0]++;
}
void Block::set_Figure2()
{
	for (int i = 0; i < figure.size() - 1; i++)
	{
		for (int j = 0; j < figure[i].size() - 2; j++)
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
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i > 1) || j)
				figure[i][j]++;
}
void Block::set_Figure4()
{
	for (int i = 0; i < figure.size() - 2; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			figure[i][j]++;
}
void Block::set_Figure5()
{
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i) || (j && i < 2))
				figure[i][j]++;
}
void Block::set_Figure6()
{
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i == 1) || j)
				figure[i][j]++;
}
void Block::set_Figure7()
{
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i < 2) || (j && i))
				figure[i][j]++;
}
/********** End set figures ***********/

void Block::arrangeMatrix()
{
	if (isRowZeroEmpty())
	{
		pullFigureUp();
		arrangeMatrix();
	}
	if (isColumnZeroEmpty())
	{
		pullFigureLeft();
		arrangeMatrix();
	}
}

bool Block::isRowZeroEmpty()
{
	for (int i = 0; i < BLOCK_MATRIX; i++)
		if (figure[i][0])
			return false;
	return true;
}

bool Block::isColumnZeroEmpty()
{
	for (int i = 0; i < figure[0].size(); i++)
		if (figure[0][i])
			return false;
	return true;
}

void Block::DropRows(const uint& row)
{
	for (int i = 0; i < figure.size(); i++)
		for (int j = row; j > 0; j--)
			swap(figure[i][j], figure[i][j - 1]);

	for (int i = 0; i < figure.size(); i++)
		figure[i][0] = 0;
}

void Block::pullFigureUp()
{
	for (int i = 0; i < figure.size(); i++)
		for (int j = 0; j < figure[i].size() - 1; j++)
			swap(figure[i][j], figure[i][j + 1]);
}

void Block::pullFigureLeft()
{
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size(); j++)
			swap(figure[i][j], figure[i + 1][j]);
}

void Block::move(int dir)
{
	cleanPrint();
	switch (dir)
	{
	case DROP:
		pos.move(DOWN);
		break;
	case MOVE_LEFT:
		pos.move(LEFT);
		break;
	case MOVE_RIGHT:
		pos.move(RIGHT);
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

void Block::cleanBlock()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			figure[i][j] = 0;
}

void Block::cleanPrint() const
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

void Block::drawBlock() {

#ifdef ___COLORS___
	setTextColor(color);
#endif

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (figure[i][j])
			{
				gotoxy(pos.getX() + i, pos.getY() + j);
				cout << shape;
			}
		}
	}
#ifdef ___COLORS___
	setTextColor(WHITE);
#endif
}

void Block::drawMatrix()
{
	for (int i = 0; i < figure.size(); ++i)
		for (int j = 0; j < figure[i].size(); ++j)
		{
			gotoxy(pos.getX() + i, pos.getY() + j);
			if (figure[i][j])
				setTextColor(RED);
			cout << figure[i][j];
			setTextColor(WHITE);
		}
}

void Block::moveDown()
{
	cleanPrint();
	pos.move(DOWN);
	drawBlock();
}

void Block::moveLeft()
{
	cleanPrint();
	pos.move(LEFT);
	drawBlock();
}

void Block::moveRight()
{
	cleanPrint();
	pos.move(RIGHT);
	drawBlock();
}



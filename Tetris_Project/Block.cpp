#include "Block.h"

Block::Block(Point _pos) : pos(_pos), shape(SHAPE)
{
	random_device rnd;
	const uniform_int_distribution<> shapeRange(0, 6);
	const uniform_int_distribution<> colorRange(1, 14);
	shapeNum = (shapeRange(rnd));
	color = static_cast<Color>(colorRange(rnd));
	cleanBlock();
	setFigure();
}

bool Block::colorsMode = false;

Block& Block::operator=(const Block& b)
{
	if (&b != this)
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
	const uniform_int_distribution<> shapeRange(0, 6);
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
	case LINE:
		setLineFigure();
		break;
	case L:
		setLfigure();
		break;
	case LEFT_L:
		setLeftLfigure();
		break;
	case DICE:
		setDiceFigure();
		break;
	case RIGHT_STEPS:
		setRightStepsFigure();
		break;
	case CENTER_STEP:
		setCenterStepsFigure();
		break;
	case LEFT_STEPS:
		setLeftStepsFigure();
		break;

	default:
		break;
	}
}

//This function sets the figure of the 1st block
void Block::setLineFigure()
{
	for (int i = 0; i < figure.size(); i++)
		figure[i][0]++;
}

//This function sets the figure of the 2nd block
void Block::setLfigure()
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

//This function sets the figure of the 3rd block
void Block::setLeftLfigure()
{
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i > 1) || j)
				figure[i][j]++;
}

//This function sets the figure of the 4th block
void Block::setDiceFigure()
{
	for (int i = 0; i < figure.size() - 2; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			figure[i][j]++;
}

//This function sets the figure of the 5th block
void Block::setRightStepsFigure()
{
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i) || (j && i < 2))
				figure[i][j]++;
}

//This fucntion sets the figure of the 6th block.
void Block::setCenterStepsFigure()
{
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i == 1) || j)
				figure[i][j]++;
}

//This function sets the figure of the 7th block
void Block::setLeftStepsFigure()
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

//This function checks if the first row is empty
bool Block::isRowZeroEmpty()
{
	for (int i = 0; i < BLOCK_MATRIX; i++)
		if (figure[i][0])
			return false;
	return true;
}

//This function checks if the first collumn is empty
bool Block::isColumnZeroEmpty()
{
	for (int i = 0; i < figure[0].size(); i++)
		if (figure[0][i])
			return false;
	return true;
}

void Block::DropRows(const uint& row)
{
	if (row)
	{
		for (int i = 0; i < figure.size(); i++)
			for (int j = row; j > 0; j--)
				std::swap(figure[i][j], figure[i][j - 1]);
	}
	for (int i = 0; i < figure.size(); i++)
		figure[i][0] = 0;
}

void Block::pullFigureUp()
{
	for (int i = 0; i < figure.size(); i++)
		for (int j = 0; j < figure[i].size() - 1; j++)
			std::swap(figure[i][j], figure[i][j + 1]);
}

void Block::pullFigureLeft()
{
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size(); j++)
			std::swap(figure[i][j], figure[i + 1][j]);
}

// This function cleans the block (by reseting the matrix that holds the block's figure)
void Block::cleanBlock()
{
	//	pos = { 0,0 };
	//shapeNum = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			figure[i][j] = 0;
}

void Block::cleanPrint() const
{
	for (size_t i = 0; i < figure.size(); i++)
	{
		for (size_t j = 0; j < figure[i].size(); j++)
		{
			gotoxy(pos.getX() + i, pos.getY() + j);
			cout << EMPTY_CELL;
		}
	}
}

// This function rotates the block clockwise
void Block::clockwiseRotate()
{
	if (shapeNum == 4)
		return;
	transpose_Matrix();
	reverseColumns();
	arrangeMatrix();
}

// this function rotates the block counter clockwise
void Block::counterClockwiseRotate()
{
	if (shapeNum == 4)
		return;
	transpose_Matrix();
	reverseRows();
	arrangeMatrix();
}

// This fucntion tranpose the matrix (swaps the collumn and the rows)
void Block::transpose_Matrix()
{
	for (size_t i = 0; i < figure.size(); i++)
		for (size_t j = i + 1; j < figure[i].size(); j++)
			std::swap(figure[i][j], figure[j][i]);
}

// This function 
void Block::reverseRows()
{
	for (size_t i = 0; i < BLOCK_MATRIX; i++)
	{
		size_t start = 0;
		size_t end = BLOCK_MATRIX - 1;


		while (start < end)
		{
			swap(figure[i][start], figure[i][end]);
			start++;
			end--;
		}
	}
}

void Block::reverseColumns()
{
	for (int i = 0; i < BLOCK_MATRIX; i++)
	{
		int start = 0;
		int end = BLOCK_MATRIX - 1;


		while (start < end)
		{
			swap(figure[start][i], figure[end][i]);
			start++;
			end--;
		}
	}
}

void Block::drawBlock() const
{
	if (colorsMode)
		setTextColor(color);

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
	if (colorsMode)
		setTextColor(WHITE);
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
	pos++;
	drawBlock();
}

void Block::moveLeft()
{
	cleanPrint();
	pos <<= 1;
	drawBlock();
}

void Block::moveRight()
{
	cleanPrint();
	pos >>= 1;
	drawBlock();
}

void Block::changeColorsMode()
{
	if (Block::colorsMode)
		colorsMode = false;
	else
		colorsMode = true;
}

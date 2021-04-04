#include "Board.h"

#include "io_utils.h"


void Board::drawBoard()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			gotoxy(pos.getX() + i, pos.getY() + j);
			cout << board[i][j];
		}
	}
}

void Board::drawBlocksInBoard()
{
	for (int i = 0; i < blocks.size(); i++)
		blocks[i].drawBlock();
}


void Board::drawBoundaries()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (!i || i == width - 1 || j == length - 1)
			{
				gotoxy(pos.getX() + i, pos.getY() + j);
				cout << board[i][j];
			}
		}
	}
}
Board::Board(Point _pos, unsigned int _len, unsigned int _width) : pos(_pos), length(_len), width(_width)
{
	allocateSize();
	initialEmptyCells();
}

void Board::cleanBoard()
{
	for(int i=1;i<width-1;i++)
		for (int j = 0; j < length - 1; j++)
			board[i][j] = EMPTY_CELL;
}


void Board::allocateSize()
{
	board.resize(width);
	for (int i = 0; i < width; i++)
		board[i].resize(length);
}

void Board::initialEmptyCells()
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++)
			board[i][j] = EMPTY_CELL;
	for (int i = 0; i < width; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			gotoxy(pos.getX() + i, pos.getY() - j);
			cout << EMPTY_CELL;
		}
	}
}


void Board::setBottomBoundary()
{
	for (int i = 0; i < width; i++)
		board[i][length - 1] = FLOOR;
}

void Board::setTopBoundary()
{
	for (int i = 0; i < width; i++)
		board[i][0] = FLOOR;
}

void Board::setLeftBoundary()
{
	for (int i = 0; i < length; i++)
		board[0][i] = WALL;
}

void Board::setRightBoundary()
{
	for (int i = 0; i < length; i++)
		board[width - 1][i] = WALL;
}

void Board::setAllBoundaries()
{
	setTopBoundary();
	setRightBoundary();
	setLeftBoundary();
	setBottomBoundary();
	board[0][0] = UP_LEFT;
	board[width - 1][0] = UP_RIGHT;
	board[0][length - 1] = DOWN_LEFT;
	board[width - 1][length - 1] = DOWN_RIGHT;
}


void Board::freezeBlock(Block& block)
{
	int x, y;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block.figure[i][j])
				board[x = block.pos.getX() + i - pos.getX()][y = block.pos.getY() + j - pos.getY()] = block.shape;		
		}
	}
	block.shape = SHAPE_AFTER_FREEZE;
	blocks.push_back(block);
}

void Board::resizeBoundaries(const unsigned& x, const unsigned& y)
{
	int tempW = width, tempL = length;
	width = x;
	length = y;
	allocateSize();
	if (width > tempW)
		for (int i = tempW; i < width; i++)
			for (int j = 0; j < length; j++)
				board[i][j] = EMPTY_CELL;
	if (length > tempL)
		for (int i = 0; i < width; i++)
			for (int j = tempL; j < length; j++)
				board[i][j] = EMPTY_CELL;
}

int Board::checkBoard()
{
	int count = 0;
	for (int i = 3; i < length - 1; i++)
	{
		if (isFullRow(i))
		{
			dropRows(i);
			drawBoard();
			count++;
		}
	}
	
	return count;
}

bool Board::isFullRow(const int& row)
{
	for (int i = 1; i < width - 1; i++)
		if (board[i][row] == ' ')
			return false;
	return true;
}

void Board::dropRows(const int& row)
{
	for (int i = 1; i < BOARD_WIDTH - 1; i++)
		for (int j = row; j > 4; j--)
			board[i][j] = board[i][j - 1];
}

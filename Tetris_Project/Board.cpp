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

Board::Board(Point _pos, unsigned int _len, unsigned int _width) : pos(_pos), length(_len), width(_width)
{
	allocateSize();
	initialEmptyCells();
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
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block.figure[i][j])
				board[block.pos.getX() + i - pos.getX()][block.pos.getY() + j - pos.getY()] = block.shape;
		}
	}
	//block.cleanBlock();
	drawBoard();
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



bool Board::checkLocation(const Block& block, int direction)
{
	//Brick b;
	//
	//for(int i=0;i<4;i++)
	//{

	//	
	//}
	return true;
}

#include "Board.h"

Board::Board(const Point& _pos, uint _len, uint _width) : pos(_pos), length(_len), width(_width)
{
	allocateSize();
	initialEmptyCells();
}

void Board::drawBoard()const
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

void Board::cleanBoard()
{
	for(int i=1;i<width-1;i++)
		for (int j = 1; j < length - 1; j++)
			board[i][j] = EMPTY_CELL;
	blocks.clear();
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

void Board::setSeparators(uint const& row)
{
	for (int i = 0; i < width; i++)
	{
		if (i && i < width - 1)
			board[i][row] = FLOOR;
		else if (i)
			board[i][row] = RIGHT_CONNECTOR;
		else
			board[i][row] = LEFT_CONNECTOR;
	}
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
	block.shape = SHAPE_AFTER_FREEZE;
	blocks.push_back(block);
}

void Board::resizeBoundaries(const int& x, const int& y)
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

uint Board::checkBoard()
{
	ushort count = 0;
	for (size_t i = 1; i < length - 1; i++)
	{
		if (isFullRow(i))
		{
			dropRows(i);
			drawBlocksInBoard();
			drawBoundaries();
			count++;
			return count + checkBoard();
		}
	}
	return count;
}

bool Board::isFullRow(const uint& row)
{
	for (int i = 1; i < width - 1; i++)
		if (board[i][row] == EMPTY_CELL)
			return false;
	return true;
}

void Board::dropRows(const uint& row)
{
	dropBlocks(row);
	for (int i = 1; i < width - 1; i++)
	{
		for (int j = row; j > 1; j--)
		{
			board[i][j] = board[i][j - 1];
			gotoxy(pos.getX() + i, pos.getY() + j);
			cout << board[i][j];
		}	
	}
	drawBlocksInBoard();
}

void Board::dropBlocks(const uint& row)
{
	int temp = 0;
	for (int i = 0; i < blocks.size(); ++i)
	{
		if (temp = isFigureInRow(blocks[i], row) >= 0)
			blocks[i].DropRows(temp);
		else if (temp == -1)
			blocks[i].moveDown();
	}
}

int Board::isFigureInRow(Block& block, const uint& row)const 
{
	if (block.pos.getY() + block.figure[0].size() < pos.getY() + row)
		return -1;
	for (int i = 0; i < block.figure[0].size(); ++i)
	{
		if ((block.pos.getY() + i == pos.getY() + row))
			return i;
	}
	return -2;
}

void Board::fillAllBoard(const uchar& shape)
{
	for (size_t i = 0; i < board.size(); ++i)
		for (size_t j = 0; j < board[i].size(); ++j)
			board[i][j] = shape;
}


#include "Board.h"

#include "io_utils.h"


void Board::drawBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			gotoxy(pos.getX() + i, pos.getY() + j);
			cout << board[i][j];
		}
	}
}

Board::Board(Point _pos) : pos(_pos)
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{

			if (j == BOARD_LENGTH - 1)
			{
				if (i > 0 && i < BOARD_WIDTH - 1)
					board[i][j] = FLOOR;
				else if (i == 0)
					board[i][j] = DOWN_LEFT;
				else
					board[i][j] = DOWN_RIGHT;
			}
			else if ((i == 0 || i == BOARD_WIDTH - 1) && (j != BOARD_LENGTH - 1))
				board[i][j] = WALL;
			else
				board[i][j] = EMPTY_CELL;
		}
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
	block.cleanBlock();
	drawBoard();
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

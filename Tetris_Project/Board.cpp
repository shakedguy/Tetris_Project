#include "Board.h"

#include "io_utils.h"


void Board::drawBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			board[i][j].draw();
		}
	}
}

Board::Board(Point _pos) : pos(_pos)
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			board[i][j].setPos(pos.getX() + i, pos.getY() + j);
			if (j == BOARD_LENGTH - 1)
			{
				if (i > 0 && i < BOARD_WIDTH - 1)
					board[i][j].setShape(FLOOR);
				else if (i == 0)
					board[i][j].setShape(DOWN_LEFT);
				else
					board[i][j].setShape(DOWN_RIGHT);
			}
			else if ((i == 0 || i == BOARD_WIDTH - 1) && (j != BOARD_LENGTH - 1))
				board[i][j].setShape(WALL);
			else
				board[i][j].setShape(EMPTY_CELL);
		}
	}
}

void Board::freezeBlock(const Block& block)
{
	for (Point i : block.type)
	{
		board[i.getX() - pos.getX()][i.getY() - pos.getY()].setShape(i.getShape());
		board[i.getX() - pos.getX()][i.getY() - pos.getY()].draw();
	}
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

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
			if ((i == 0 || i == BOARD_WIDTH - 1) && (j != BOARD_LENGTH - 1))
				board[i][j].setShape(WALL);
		}
	}
}

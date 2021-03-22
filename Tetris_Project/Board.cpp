#include "Board.h"

#include "io_utils.h"


void Board::drawBoard(Point pos)
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			board[i][j].setPos(pos.getX() + i, pos.getY() + j);
			if (j == BOARD_LENGTH - 1)
			{
				if (i > 0 && i < BOARD_WIDTH - 1)
					board[i][j].draw(FLOOR);
				else if (i == 0)
					board[i][j].draw(DOWN_LEFT);
				else
					board[i][j].draw(DOWN_RIGHT);
			}
			if ((i == 0 || i == BOARD_WIDTH - 1) && (j != BOARD_LENGTH - 1))
				board[i][j].draw(WALL);
		}
	}
}

void Board::drawBox(Point pos)
{
	for (int i = 0; i < BOX_WIDTH; i++)
	{
		for (int j = 0; j < BOX_LENGTH; j++)
		{
			box[i][j].setPos(pos.getX() + i, pos.getY()+ j);
			if (j == 0 || j == BOX_LENGTH - 1)
			{
				if (j == 0 && i == 0)
					box[i][j].draw(UP_LEFT);
				else if (j == 0 && i == BOX_WIDTH - 1)
					box[i][j].draw(UP_RIGHT);
				else if (i > 0 && i < BOX_WIDTH - 1)
					box[i][j].draw(FLOOR);
				else if (j == BOX_LENGTH - 1 && i == 0)
					box[i][j].draw(DOWN_LEFT);
				else if (j == BOX_LENGTH - 1 && i == BOX_WIDTH - 1)
					box[i][j].draw(DOWN_RIGHT);

			}
			if ((i == 0 || i == BOX_WIDTH - 1) && (j != 0 && (j != BOX_LENGTH - 1)))
				box[i][j].draw(WALL);
		}
	}
}
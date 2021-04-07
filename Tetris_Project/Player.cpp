
#include "Player.h"

#include "Game.h"

Player::Player(int _playerNum, Point _boardPos, Point _boxPos) : playerNum(_playerNum),
boardPos(_boardPos), boxPos(_boxPos), board(boardPos, BOARD_LENGTH, BOARD_WIDTH), box(boxPos), direction(DEFAULT)
{
	if (playerNum == 1)
		block.pos = { LEFT_CURRENT_BLOCK };
	else
		block.pos = { RIGHT_CURRENT_BLOCK };
	score = 0;
	setGameBoundaries();
}

void Player::setName()
{
	gotoxy(WINNING_MASSAGE);
	cout << "Please enter player " << playerNum << " name: ";
	cin >> name;
	clear_screen();
}

void Player::clearGame()
{
	board.cleanBoard();
	box.clearBox();
	block.createNewBlock();
	setGameBoundaries();
	if (playerNum == 1)
		block.pos = { LEFT_CURRENT_BLOCK };
	else
		block.pos = { RIGHT_CURRENT_BLOCK };
}

void Player::setGameBoundaries()
{
	board.setAllBoundaries();
	for (size_t i = 0; i < board.width; ++i)
		board.board[i][0] = EMPTY_CELL;
}

bool Player::isLost()
{
	for (unsigned int i = 1; i < board.width - 1; ++i)
		if (board.board[i][1] != EMPTY_CELL)
			return true;
	return false;
}

void Player::printScore() const
{
#ifdef ___COLORS___
	setTextColor(LIGHTCYAN);
#endif
	
	Point pos;
	if (playerNum == 1)
		pos = { LEFT_SCORE_POS };
	else
		pos = { RIGHT_SCORE_POS };
	gotoxy(pos.getX(), pos.getY());
	cout << name << "'s score: ";
	gotoxy(pos.getX() + 5, pos.getY() + 1);
	cout << score;
	
#ifdef ___COLORS___
	setTextColor(WHITE);
#endif

}

void Player::setPlayerKeys(const char* keys) {

	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
	arrowKeys[4] = keys[4];
}

bool Player::drop()
{
	while (moveDown()){}
	direction = DEFAULT;
	return false;
}

int Player::getDirection(char key)
{
	for (int i = 0; i < 5; i++)
	{
		if (key == arrowKeys[i] || key == (arrowKeys[i] - 32))
				return i;
	}
	return -1;
}

bool Player::isDown(const char& key)
{
	if (arrowKeys[DROP] == key || (arrowKeys[DROP] - 32) == key)
		return true;
	return false;
}

char Player::getKey(const int& dir)
{
	if (dir < arrowKeys.size())
		return arrowKeys[dir];
	return 0;
}

void Player::getNewBlock()
{
	block = box.blocks[0];
	if (playerNum == 1)
		block.pos = { LEFT_CURRENT_BLOCK };
	else
		block.pos = { RIGHT_CURRENT_BLOCK };
	const Point temp = box.blocks[0].pos;
	box.blocks[0] = box.blocks[1];
	box.blocks[0].pos = temp;
	box.blocks[1].createNewBlock();
}

void Player::move()
{
	if (!makeTheMove() && direction == DEFAULT)
	{
		board.freezeBlock(block);
		getNewBlock();
		box.drawBox();
		block.drawBlock();
	}
	board.drawBlocksInBoard();
	board.drawBoundaries();
	int num = board.checkBoard();
	score += (num * num * POINTS_FOR_FULL_ROW);
}

bool Player::makeTheMove()
{
	switch (direction)
	{
	case COUNTER_CLOCKWISE:
		return counterClockwiseRotate();
	case CLOCKWISE:
		return clockwiseRotate();
	case DROP:
		return drop();
	case MOVE_LEFT:
		return moveLeft();
	case MOVE_RIGHT:
		return moveRight();
		
		default:
			return moveDown();
	}
}

bool Player::moveDown()
{
	if (block.pos.getY() < board.pos.getY())
	{
		block.moveDown();
		return true;
	}
	for (int i = 0; i < block.figure.size(); i++)
	{
		for (int j = 0; j < block.figure[i].size(); j++)
		{
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i - boardPos.getX()][block.pos.getY() + j + 1 - boardPos.getY()] != ' '))
				return false;
		}
	}
	block.moveDown();
	return true;
}

bool Player::moveLeft()
{
	if (block.pos.getY() < board.pos.getY())
		return moveLeftAboveBoard();
	for (int i = 0; i < block.figure.size(); i++)
	{
		for (int j = 0; j < block.figure[i].size(); j++)
		{
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i - 1 - boardPos.getX()][block.pos.getY() + j - boardPos.getY()] != EMPTY_CELL))
				return false;
		}
	}
	block.moveLeft();
	return true;
}

bool Player::moveLeftAboveBoard()
{
	if (block.pos.getX() > board.pos.getX() + 1)
	{
		block.moveLeft();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove();
}

bool Player::moveRight()
{
	if (block.pos.getY() < board.pos.getY())
		return moveRightAboveBoard();
	for (int i = 0; i < block.figure.size(); i++)
	{
		for (int j = 0; j < block.figure[i].size(); j++)
		{
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i + 1 - boardPos.getX()][block.pos.getY() + j - boardPos.getY()] != EMPTY_CELL))
				return false;
		}
	}
	block.moveRight();
	return true;
}

bool Player::moveRightAboveBoard()
{
	if (block.pos.getX() + block.figure.size() < board.pos.getX() + board.board.size() - 1)
	{
		block.moveRight();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove();
}

bool Player::clockwiseRotate()
{
	if (block.pos.getY() + block.figure[0].size() >= board.pos.getY() + board.board[0].size())
		return false;
	Block temp = block;
	temp.clockwiseRotate();
	if (block.pos.getY() < board.pos.getY())
		return rotateAboveBoard(temp);
	for (int i = 0; i < block.figure.size(); i++)
	{
		for (int j = 0; j < block.figure[i].size(); j++)
		{
			if (temp.figure[i][j] &&
				(board.board[temp.pos.getX() + i - boardPos.getX()][temp.pos.getY() + j - boardPos.getY()] != EMPTY_CELL))
				return false;
		}
	}
	block.cleanPrint();
	block = temp;
	block.drawBlock();
	return true;
}

bool Player::rotateAboveBoard(const Block& temp)
{
	if ((block.pos.getX() > board.pos.getX()) &&
		(block.pos.getX() + block.figure.size() < board.pos.getX() + board.board.size() - 1))
		
	{
		block.cleanPrint();
		block = temp;
		block.drawBlock();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove();
}

bool Player::counterClockwiseRotate()
{
	if (block.pos.getY() + block.figure[0].size() >= board.pos.getY() + board.board[0].size())
		return false;
	Block temp = block;
	temp.counterClockwiseRotate();
	if (block.pos.getY() < board.pos.getY())
		return rotateAboveBoard(temp);
	for (int i = 0; i < block.figure.size(); i++)
	{
		for (int j = 0; j < block.figure[i].size(); j++)
		{
			if (temp.figure[i][j] &&
				(board.board[temp.pos.getX() + i - boardPos.getX()][temp.pos.getY() + j - boardPos.getY()] != EMPTY_CELL))
				return false;
		}
	}
	block.cleanPrint();
	block = temp;
	block.drawBlock();
	return true;
}



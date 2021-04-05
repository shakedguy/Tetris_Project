
#include "Player.h"

#include "Game.h"

Player::Player(int _playerNum, Point _boardPos, Point _boxPos) : playerNum(_playerNum),
boardPos(_boardPos), boxPos(_boxPos), board(boardPos, BOARD_LENGTH, BOARD_WIDTH), box(boxPos), direction(1)
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

void Player::changeBlockPos(const Point& pos)
{
	block.pos = { pos };
}

void Player::clearGame()
{
	board.cleanBoard();
	box.clearBox();
	block.createNewBlock();
	if (playerNum == 1)
		block.pos = { LEFT_CURRENT_BLOCK };
	else
		block.pos = { RIGHT_CURRENT_BLOCK };
	setName();
}

void Player::setGameBoundaries()
{
	board.setBottomBoundary();
	board.setLeftBoundary();
	board.setRightBoundary();
	board.board[0][BOARD_LENGTH - 1] = DOWN_LEFT;
	board.board[BOARD_WIDTH - 1][BOARD_LENGTH - 1] = DOWN_RIGHT;
	for (int i = 0; i < 7; i++)
	{
		board.board[0][i] = EMPTY_CELL;
		board.board[board.width - 1][i] = EMPTY_CELL;
	}
}

bool Player::isLost()
{
	for (int i = 0; i < board.width; i++)
		if (board.board[i][6] != ' ')
			return true;
	return false;
}


void Player::printScore()
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

void Player::move()
{
	if (direction == DROP)
		drop();
	else if (checkStep())
		block.move(direction);
	else if (direction == DOWN)
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

void Player::drop()
{
	while (checkStep())
		block.move(direction);
}

int Player::getDirection(char key)
{
	for (int i = 0; i < 5; i++)
	{
		if (key == arrowKeys[i] || key == (arrowKeys[i] - 32))
			if (i == 1)
				return DROP;
			else
				return i;
	}
	return -1;
}

bool Player::isDown(const char& key)
{
	if (arrowKeys[DOWN] == key || (arrowKeys[DOWN] - 32) == key)
		return true;
	return false;
}

char Player::getKey(const int& dir)
{
	if (dir == DROP)
		return arrowKeys[DOWN];
	else if (dir == DOWN)
		return 0;
	return arrowKeys[dir];
}



void Player::getNewBlock()
{
	block = box.blocks[0];
	if (playerNum == 1)
		block.pos = { LEFT_CURRENT_BLOCK };
	else
		block.pos = { RIGHT_CURRENT_BLOCK };
	Point temp = box.blocks[0].pos;
	box.blocks[0] = box.blocks[1];
	box.blocks[0].pos = temp;
	box.blocks[1].createNewBlock();
}

bool Player::checkStep()
{
	switch (direction)
	{
	case DROP:
		if (check_Down())
			return true;
		return false;
	case LEFT:
		if (check_Left())
			return true;
		return false;
	case RIGHT:
		if (check_Right())
			return true;
		return false;
	case DOWN:
		if (check_Down())
			return true;
		return false;
	default:
		return true;
	}
}

bool Player::check_Down()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i - boardPos.getX()][block.pos.getY() + j + 1 - boardPos.getY()] != ' '))
				return false;
		}
	}		
	return true;
}

bool Player::check_Left()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i - 1 - boardPos.getX()][block.pos.getY() + j - boardPos.getY()] != ' '))
				return false;
		}
	}
	return true;
}

bool Player::check_Right()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i + 1 - boardPos.getX()][block.pos.getY() + j - boardPos.getY()] != ' '))
				return false;
		}
	}
	return true;
}








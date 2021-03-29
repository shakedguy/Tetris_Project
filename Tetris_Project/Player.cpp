#include "Player.h"


void Player::setName()
{
	name = "Guy";
	//cout << "Please enter player " << playerNum << " name: ";
	//cin >> name;
}
void Player::printScore()
{
	Point pos;
	if (!playerNum)
		pos.setPos(LEFT_SCORE_POS);
	else
		pos.setPos(RIGHT_SCORE_POS);
	gotoxy(pos.getX(), pos.getY());
	cout << name << "'s score:";
	gotoxy(pos.getX(), pos.getY() + 1);
	cout << "                 ";
	gotoxy(pos.getX(), pos.getY() + 1);
	cout << score;
}
void Player::setPlayerKeys(const char* keys) {

	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
}

void Player::move()
{
	if (checkStep())
		block.move(direction);
	else if (direction == DOWN)
	{
		board.freezeBlock(block);
		getNewBlock();
		board.drawBoard();
	}
		
}

int Player::getDirection(char key)
{
	for (int i = 0; i < 4; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}

void Player::getNewBlock()
{
	block.cleanBlock();
	block = box.blocks[0];
	if (playerNum == 1)
		block.setPos(LEFT_CURRENT_BLOCK );
	else
		block.setPos(RIGHT_CURRENT_BLOCK );
	block.printBrick();
	box.blocks[0].cleanBlock();

}

bool Player::checkStep()
{
	switch (direction)
	{
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
	for(Point& i:block.type)
		if (board.board[i.getX() - board.pos.getX()][(i.getY() + 1) - board.pos.getY()].getShape() != EMPTY_CELL)
			return false;			
	return true;
}

bool Player::check_Left()
{
	for (Point& i : block.type)
		if (board.board[(i.getX() - 1) - board.pos.getX()][i.getY() - board.pos.getY()].getShape() != EMPTY_CELL)
			return false;
	return true;
}

bool Player::check_Right()
{
	for (Point& i : block.type)
		if (board.board[(i.getX() + 1) - board.pos.getX()][i.getY() - board.pos.getY()].getShape() != EMPTY_CELL)
			return false;
	return true;
}








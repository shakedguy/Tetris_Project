﻿#include "Player.h"


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
		//board.drawBoard();
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
	if (playerNum == 1)
		block.setPos(LEFT_CURRENT_BLOCK );
	else
		block.setPos(RIGHT_CURRENT_BLOCK );
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
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block.figure[i][j] && (board.board[block.pos.getX() + i - boardPos.getX()][block.pos.getY() + j + 1 - boardPos.getY()] != ' '))
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
			if (block.figure[i][j] && (board.board[block.pos.getX() + i - 1 - boardPos.getX()][block.pos.getY() + j - boardPos.getY()] != ' '))
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
			if (block.figure[i][j] && (board.board[block.pos.getX() + i + 1 - boardPos.getX()][block.pos.getY() + j - boardPos.getY()] != ' '))
				return false;
		}
	}
	return true;
}








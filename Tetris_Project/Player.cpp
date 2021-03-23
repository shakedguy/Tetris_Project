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
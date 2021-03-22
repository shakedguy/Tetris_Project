#include "Player.h"


void Player::setName(int playerNum)
{
	num = playerNum;
	name = "Guy";
	//cout << "Please enter player " << playerNum << " name: ";
	//cin >> name;
}
void Player::printScore()
{
	if (num == 1)
	{
		gotoxy(LEFT_BOX_X, SCORES_Y);
		cout << name << "'s score:";
		gotoxy(LEFT_BOX_X, SCORES_Y + 1);
		cout << "                 ";
		gotoxy(LEFT_BOX_X, SCORES_Y + 1);
		
	}
	else
	{
		gotoxy(RIGHT_BOX_X, SCORES_Y);
		cout << name << "'s score:";
		gotoxy(RIGHT_BOX_X, SCORES_Y + 1);
		cout << "                 ";
		gotoxy(RIGHT_BOX_X, SCORES_Y + 1);
	}
	cout << score;
}
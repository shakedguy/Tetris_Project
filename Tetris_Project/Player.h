/***************************************
	Header file for class "Player".
***************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "io_utils.h"
#include "Point.h"
#include "Public const and structs.h"
using namespace std;
#include <iostream>


class Player
{
	string name;
	int playerNum;
	int score;
public:
	Player(int _playerNum) : playerNum(_playerNum), score(0)
	{
		//cout << "Please enter player " << (playerNum + 1) << " name: ";
		//cin >> name;
		//clear_screen();
		name = "guy";
	}
	void setName();
	void printScore();
};

#endif
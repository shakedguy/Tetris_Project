/***************************************
	Header file for class "Player".
***************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "io_utils.h"
#include "Point.h"
#include "Board.h"
#include "Box.h"
#include "Public const and structs.h"
using namespace std;
#include <iostream>


class Player
{
	string name;
	int playerNum;
	int direction;
	char arrowKeys[4];
	Point boardPos;
	Point boxPos;
	Board board;
	Box box;
	Block block;
	int score;

public:
	Player() : Player(0, { 0,0 }, { 0,0 }) {}
	Player(int _playerNum, Point _boardPos, Point _boxPos) : playerNum(_playerNum), boardPos(_boardPos), boxPos(_boxPos),
		board(boardPos), box(boxPos), direction(1)
	{
		//cout << "Please enter player " << (playerNum + 1) << " name: ";
		//cin >> name;
		//clear_screen();
		name = "guy";
		if (playerNum == 1)
			block.setPos({ LEFT_CURRENT_BLOCK });
		else
			block.setPos({ RIGHT_CURRENT_BLOCK });
		block.setFigure();
		score = 0;
		Sleep(100);
	}
	void setName();
	void printScore();
	void drawBoard() { board.drawBoard(); box.drawBox(); }
	void setPlayerKeys(const char* keys);
	void move();
	int getDirection(char key);
	void setDirection(int key) { direction = key; }
	bool checkStep();
	void getNewBlock();
	bool check_Left();
	bool check_Right();
	bool check_Down();
};

#endif
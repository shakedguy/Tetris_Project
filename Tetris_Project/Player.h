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
	array<char, 5> arrowKeys;
	Point boardPos;
	Point boxPos;
	Board board;
	Box box;
	Block block;
	int score;

private:
	void setGameBoundaries();
	bool drop();
	bool moveLeftAboveBoard();
	bool moveRightAboveBoard();
	bool rotateAboveBoard(const Block& temp);
	

public:
	Player() : Player(0, { 0,0 }, { 0,0 }) {}
	Player(int _playerNum, Point _boardPos, Point _boxPos);
	~Player() = default;
	void setName();
	void printScore()const;
	void drawBoard() { board.drawBoard(); box.drawBox(); }
	void setPlayerKeys(const char* keys);
	void move();
	int getDirection(char key);
	void setDirection(const int& dir) { direction = dir; }
	bool makeTheMove();
	void getNewBlock();
	bool clockwiseRotate();
	bool counterClockwiseRotate();
	bool moveLeft();
	bool moveRight();
	bool moveDown();
	bool isLost();
	void setCurrentBlockPos(const Point& pos) { block.pos = pos; }
	void clearGame();
	string getName()const { return name; }
	bool isDown(const char& key);
	char getKey(const int& dir);
	unsigned int getScore()const { return score; }
};

#endif
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
	ushort playerNum;
	ushort direction;
	array<uchar, 5> arrowKeys;
	Point boardPos;
	Point boxPos;
	Board board;
	Box box;
	Block block;
	uint score;

private:
	void setGameBoundaries();
	bool drop();
	bool moveLeftAboveBoard();
	bool moveRightAboveBoard();
	bool rotateAboveBoard(const Block& temp);
	void getNewBlock();
	bool makeTheMove();
	bool clockwiseRotate();
	bool counterClockwiseRotate();
	bool moveLeft();
	bool moveRight();
	bool moveDown();

public:
	Player() : Player(0, { 0,0 }, { 0,0 }) {}
	Player(ushort _playerNum, Point _boardPos, Point _boxPos);
	~Player() = default;
	void setName();
	void printScore()const;
	void drawBoard()const { board.drawBoard(); box.drawBox(); }
	void setPlayerKeys(const char* keys);
	void move();
	sint getDirection(const uchar& key);
	void setDirection(const ushort& dir) { direction = dir; }
	bool isLost();
	void setCurrentBlockPos(const Point& pos) { block.pos = pos; }
	void clearGame();
	string getName()const { return name; }
	bool isDown(const uchar& key);
	char getKey(const ushort& dir);
	uint getScore()const { return score; }
};

#endif
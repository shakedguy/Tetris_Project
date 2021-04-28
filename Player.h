﻿/***************************************
	Header file for class "Player".
***************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Public_const_and_structs.h"
#include "Point.h"
#include "Board.h"
#include "Box.h"

class Player
{
	enum objectsPositions
	{
	     LEFT_SCORE = 18, RIGHT_SCORE = 68, SCORES_Y = 2,
		LEFT_BLOCK = 34, RIGHT_BLOCK = 54, BLOCKS_Y = 0
	};
	enum Constants
	{
	     POINTS_FOR_FULL_ROW = 100, BLOCKS_FOR_ACCELERATION = 5, SCORE_FOR_ACCELERATION = 20,
		INDIVATORS_WIDTH =3, INDIVATORS_LENGTH =2, NUM_OF_KEYS = 5
	};
	static bool colorsMode;
	string name;
	ushort playerNum;
	ushort direction;
	map<uchar, sint> keys;
	array<Board, NUM_OF_KEYS> keyIndicators;
	Point boardPos;
	Point boxPos;
	Board board;
	Box box;
	Block block;
	uint score;

	friend class Game;


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
	void setKeysIndication();
	void showIndicateHit(const ushort& dir);
	void drawKeysIndication() const;


public:
	Player() : Player(0, {0, 0}, {0, 0}) {}
	Player(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos);
	~Player() = default;
	friend std::ostream& operator<<(std::ostream& out, const Player& _player);
	void setName();
	void printScore() const;
	void drawBoard() const { }
	void setPlayerKeys(const string& arrowKeys);
	void move();
	sint getDirection(const uchar& key);
	void setDirection(const ushort& dir) { direction = dir; }
	bool isLost();
	void setCurrentBlockPos(const Point& pos) { block.pos = pos; }
	void clearGame();
	string getName() const { return name; }
	bool isDown(const uchar& key);
	uchar getKey(const ushort& dir) const;
	uint getScore() const { return score; }
	bool checkSpeed(const int& accNum) const;
	static void changeColorsMode();
};

#endif

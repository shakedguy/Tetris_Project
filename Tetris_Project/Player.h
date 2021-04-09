/***************************************
	Header file for class "Player".
***************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "io_utils.h"
#include "Point.h"
#include "Board.h"
#include "Box.h"
#include "Public_const_and_structs.h"
using namespace std;
#include <iostream>
#include <map>

//class Key
//{
//	map<int, char> _keys;
//
//public:
//	void add(const int& num, const char& ch)
//	{
//		_keys.insert({ num, ch });
//	}
//	void add(const string& str)
//	{
//		for (int i = 0; i < str.size(); i++)
//			_keys.insert(i, { str[i] });
//	}
//	friend ostream& operator<<(ostream& out, const Key& _key) { _key.printKeys(); return out; }
//	void printKeys()const
//	{
//		for (int i = 0; i < _keys.size(); i++)
//			cout << _keys.at(i)<< ' ';
//	}
//	const char& getKey(const int& dir)
//	{
//		return _keys[dir];
//	}
//	int& getDir(const char& key)
//	{
//		for (int i = 0; i < _keys.size(); i++)
//			if (_keys[i] == key)
//				return i;
//	}
//};

class Player
{
	static bool colorsMode;
	string name;
	ushort playerNum;
	ushort direction;
	//array<uchar, NUMBER_OF_KEYS> arrowKeys;
	map<uchar, sint> keys;
	array<Board, NUMBER_OF_KEYS> keyIndicators;
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
	void setKeysIndication();
	void showIndicateHit(const ushort& dir);
	void cleanIndicatorsHit(const ushort& dir);
	void drawKeysIndication()const;

public:
	Player() : Player(0, { 0,0 }, { 0,0 }) {}
	Player(ushort _playerNum, Point _boardPos, Point _boxPos);
	~Player() = default;
	friend ostream& operator<<(ostream& out, const Player& _player);
	void setName();
	void printScore()const;
	void drawBoard()const {  }
	void setPlayerKeys(const string& arrowKeys);
	void move();
	sint getDirection(const uchar& key);
	void setDirection(const ushort& dir) { direction = dir; }
	bool isLost();
	void setCurrentBlockPos(const Point& pos) { block.pos = pos; }
	void clearGame();
	string getName()const { return name; }
	bool isDown(const uchar& key);
	const uchar& getKey(const ushort& dir)const;
	uint getScore()const { return score; }
	static void changeColorsMode();
};

#endif
/***************************************
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
protected:
	enum objectsPositions
	{
	     LEFT_SCORE = 18, RIGHT_SCORE = 68, SCORES_Y = 2,
		LEFT_BLOCK = 34, RIGHT_BLOCK = 54, BLOCKS_Y = 0
	};
	enum Constants
	{
	     POINTS_FOR_FULL_ROW = 100, CELLS_FOR_ACCELERATION = 20, SCORE_FOR_ACCELERATION = 20,
		INDIVATORS_WIDTH =3, INDIVATORS_LENGTH =2, NUM_OF_KEYS = 5
	};
	static bool colorsMode;
	string name;
	ushort playerNum;
	ushort direction;
	array<Board, NUM_OF_KEYS> keyIndicators;
	Point boardPos;
	Point boxPos;
	Board board;
	Box box;
	Block* block = new Block;
	size_t score;

	friend class Game;

private:
	bool drop();
	void getNewBlock();
	bool makeTheMove();
	void drawKeysIndication() const;

protected:
	void setGameBoundaries();
	void setKeysIndication();
public:
	virtual ~Player() { delete block; }
	virtual Player& operator=(const Player& _player);
	friend std::ostream& operator<<(std::ostream& out, const Player* _player);
	void printScore() const;
	void move();
	bool isLost();
	void setCurrentBlockPos(const Point& pos)const { block->pos = pos; }
	void clearGame();
	string getName() const { return name; }
	virtual void setPlayerKeys(const string& arrowKeys) = 0;
	virtual sint getDirection(const uchar& key) = 0;
	virtual void setDirection(const uchar& key) = 0;
	virtual void setName() = 0;
	void showIndicateHit(const ushort& dir);
	size_t getScore() const { return score; }
	virtual bool checkSpeed(const size_t& accNum)const;
	void setBoardPos(const Point& _pos) { boardPos = _pos; board.setBoardPos(_pos); }
	void setBoxPos(const Point& _pos) { boxPos = _pos; box.setBoxPos(_pos); }
	static void changeColorsMode();
	virtual void initializeCalculate() = 0;
};

#endif

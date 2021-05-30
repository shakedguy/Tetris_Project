/***************************************
	Header file for class "Player".
***************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Public_const_and_structs.h"
#include "Point.h"
#include "Board.h"
#include "Box.h"
#include "Files_Handler.h"

class Player
{

	Files_Handler* blocksFile = nullptr, * movesFile = nullptr;
protected:

	enum Game_Modes { SIMPLE, SAVE, LOAD, SILENT };
	enum objectsPositions
	{
	     LEFT_SCORE = 18, RIGHT_SCORE = 68, SCORES_Y = 2,
		LEFT_BLOCK = 34, RIGHT_BLOCK = 54, BLOCKS_Y = 0
	};
	enum Constants
	{
		POINTS_FOR_FULL_ROW = 100,
		INDIVATORS_WIDTH = 3, INDIVATORS_LENGTH = 2, NUM_OF_KEYS = 5
	};
	static constexpr char HUMAN[] = "HumanPlayer", COMPUTER[] = "ComputerPlayer", TEST[] = "Test n";
	static constexpr size_t NAME_MASSAGE_X = 30, NAME_MASSAGE_Y = 10, CELLS_FOR_ACCELERATION = 20,
		SCORE_FOR_ACCELERATION = 300;
	
	static ushort gameMode;
	static bool colorsMode;
	string name;
	ushort playerNum;
	ushort direction;
	array<Board, NUM_OF_KEYS> keyIndicators;
	Point boardPos, boxPos;
	Board board;
	Box box;
	Block* block;
	size_t score = 0;

	//friend class Game;

private:
	bool drop(const size_t& cycle);
	bool makeTheMove(const size_t& cycle);
	void drawKeysIndication() const;
	bool clockwise(const size_t& cycle);
	bool counterClockwise(const size_t& cycle);
	bool left(const size_t& cycle);
	bool right(const size_t& cycle);
	bool down(const size_t& cycle);
	void initFiles();
	void allocateToWrite()noexcept(false);
	void allocateToRead()noexcept(false);
	void clearFilesContent();
	


protected:
	virtual void getNewBlock();
	void setGameBoundaries();
	void setKeysIndication();

public:
	Player(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos);
	Player(const Player& _player);
	virtual ~Player();
	virtual Player& operator=(const Player& _player);
	virtual Player& operator*() { return *this; }
	virtual Player* operator->() { return this; }
	friend std::ostream& operator<<(std::ostream& out, const Player* _player);
	void printScore() const;
	void move(const size_t& cycle);
	bool isLost();
	void setCurrentBlockPos(const Point& pos)const { block->pos = pos; }
	void clearGame();
	string getName() const { return name; }
	const ushort& getDirection()const { return direction; }
	void showIndicateHit(const ushort& dir);
	const size_t& getScore() const { return score; }
	bool checkSpeed(const size_t& accNum)const;
	void setBoardPos(const Point& _pos) { boardPos = _pos; board.setPos(_pos); }
	void setBoxPos(const Point& _pos) { boxPos = _pos; box.setPos(_pos); }
	static void changeColorsMode();
	const ushort& getPlayerNum()const { return playerNum; }
	const ushort& getCurrentBlockNum()const { return block->shapeNum; }
	void resetCurrentBlocksPos()const;
	Point getHighestPointInBoard()const { return board.getHighestPoint(); }
	static void changeGameMode(const ushort& mode) { Player::gameMode = mode; }
	void changeDirection(const ushort& dir) { direction = dir; }
	virtual string type()const { return "Player"; }
	virtual void setDirection(const uchar& key, const size_t& cycle) = 0;
	virtual void setName() = 0;
	virtual void initializeCalculate() = 0;
	virtual void setPlayerKeys(const string& arrowKeys) = 0;
	virtual sint getDirection(const uchar& key) = 0;
	bool isEndOfFiles()const;
	void printDataToFile()const;

	
};

#endif

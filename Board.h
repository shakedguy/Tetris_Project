/***************************************
	Header file for class "Board".
***************************************/
#ifndef _BOARD_H_
#define _BOARD_H_

#include "Public_const_and_structs.h"
#include "Block.h"
#include "Point.h"
#include "Bomb.h"

class Board
{
	enum Boundaries
	{
		WALL = 186,
		FLOOR = 205,
		UP_LEFT = 201,
		UP_RIGHT = 187,
		DOWN_LEFT = 200,
		DOWN_RIGHT = 188,
		RIGHT_CONNECTOR = 185,
		LEFT_CONNECTOR = 204
	};

	enum Sizes { LENGTH = 19, WIDTH = 14 };

	Point pos;
	uint length, width;
	vector<vector<uchar>> board;
	vector<Block> blocks;

	friend class Game;
	friend class Player;
	friend class HumanPlayer;
	friend class ComputerPlayer;
	friend class Menu;
	friend class Box;

private:
	bool isFullRow(const uint& row, const uint& start, const uint& end);
	void dropRows(const uint& startX, const uint& endX, const uint& startY, const uint& endY);
	int isFigureInRow(Block& block, const uint& row) const;
	void dropBlocks(const uint& row);
	void setTopBoundary();
	void setBottomBoundary();
	void setRightBoundary();
	void setLeftBoundary();
	void drawBoard() const;
	void setSeparators(uint const& row);
	bool moveLeftAboveBoard(Block* block);
	bool moveRightAboveBoard(Block* block);
	bool rotateAboveBoard(Block* block, const Block& temp);
	void DropBlock(Block& block);
	void drawFillCells()const;
	uint checkBoardWithoutChanges();
	void deleteBlock(const Block& block);
	void freezeWithoutSave(Block& block);
	Point findBestBombPos(Board* b, Block& temp)const;
	int explosionCheck(const Block& block);
	

public:
	Board() : Board({0, 0}, LENGTH, WIDTH) {}
	Board(const Point& _pos) : Board({_pos}, LENGTH, WIDTH) {}
	Board(uint _len, uint _width) : Board({0, 0}, _len, _width) {}
	Board(const Point& _pos, uint _len, uint _width);
	~Board() { this->blocks.clear(); this->cleanBoard(); }
	friend std::ostream& operator<<(std::ostream& out, const Board& board) { board.drawBoard(); board.drawBlocksInBoard();	return out; }
	Board& operator=(const Board& _board);
	void allocateSize();
	void initialEmptyCells();
	void setAllBoundaries();
	void freezeBlock(Block& block);
	void resizeBoundaries(const int& x, const int& y);
	uint checkBoard();
	void cleanBoard();
	void drawBoundaries();
	void drawBlocksInBoard()const;
	void fillAllBoard(const uchar& shape);
	const uint& getLength() const { return length; }
	const uint& getWidth() const { return width; }
	const size_t& getNumberOfBlocks() const { return blocks.size(); }
	void explosion(const Block& block);
	bool clockwiseRotate(Block* block);
	bool counterClockwiseRotate(Block* block);
	bool moveLeft(Block* block);
	bool moveRight(Block* block);
	bool moveDown(Block* block);
	Point findBestPos(Block* block, short& situations);
};

#endif

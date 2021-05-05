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
	bool isFullRow(const size_t& row, const size_t& start, const size_t& end);
	void dropRows(const size_t& startX, const size_t& endX, const size_t& startY);
	int isFigureInRow(Block& block, const size_t& row) const;
	void dropBlocks(const size_t& row);
	void setTopBoundary();
	void setBottomBoundary();
	void setRightBoundary();
	void setLeftBoundary();
	void drawBoard() const;
	void setSeparators(uint const& row);
	bool moveLeftAboveBoard(const Block* block)const;
	bool moveRightAboveBoard(const Block* block)const;
	bool rotateAboveBoard(const Block& temp)const;
	void DropBlock(Block& block);
	void drawFillCells()const;
	void drawEmptyCells()const;
	uint checkBoardWithoutChanges();
	void deleteBlock(const Block& block);
	void freezeWithoutSave(Block& block);
	Point findBestBombPos(Board* b, Block& temp)const;
	size_t explosionCheck(const Block& block);
	void returnBlocks();
	void fixBoard();

public:
	Board() : Board({0, 0}, LENGTH, WIDTH) {}
	Board(const Point& _pos) : Board(_pos, LENGTH, WIDTH) {}
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
	bool clockwiseRotate(const Block* block)const;
	bool counterClockwiseRotate(const Block* block)const;
	bool moveLeft(const Block* block)const;
	bool moveRight(const Block* block)const;
	bool moveDown(const Block* block)const;
	Point findBestPos(Block* block, short& situations)const;
	bool rotateCheck(Block* block, const ushort& dir)const;
};

#endif

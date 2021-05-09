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
	size_t length, width;
	Point endPos;
	vector<vector<Point>> board;


	friend class Game;
	friend class Player;
	friend class HumanPlayer;
	friend class ComputerPlayer;
	friend class Menu;
	friend class Box;

private:
	bool isFullRow(const size_t& row, const size_t& start, const size_t& end)const;
	bool isEmptyRow(const size_t& row, const size_t& start, const size_t& end)const;
	int isFigureInRow(Block& block, const size_t& row) const;
	void setTopBoundary();
	void setBottomBoundary();
	void setRightBoundary();
	void setLeftBoundary();
	void drawBoard() const;
	size_t topRow()const;
	bool moveLeftAboveBoard(const Block* block)const;
	bool moveRightAboveBoard(const Block* block)const;
	bool rotateAboveBoard(const Block& temp)const;
	void DropBlock(Block& block);
	void drawFillCells()const;
	void drawEmptyCells()const;
	void deleteBlock(const Block& block);
	Point findBestBombPos(Board* b, Block* temp)const;
	size_t explosionCheck(const Block& block)const;
	void cleanAndDeleteCalculation(Board* b, Block* temp)const;
	void checkMaxFullRows(vector<Block>& options, size_t& holes, size_t& oneToGo, size_t& maxOneToGo, size_t& fullRows, size_t& maxFullRows, Point& bestPos, Point& lowestPos,
		Point& oneToGoPos, const Block* temp, short& bestSituation, short& situation)const;
	size_t setLimit(const Block* block)const;
	bool isWellConnected(const size_t& x, const size_t& y);
	void fixBoard(const size_t& startX, const size_t& endX, const size_t& startY, const size_t& endY);
	bool notDisturbing(const Block& block)const;
	bool isBlocksAccess(const Block& block, const size_t& row)const;
	size_t countEmptyCells(const size_t& row)const;
	vector<Point> getEmptyCellsInRow(const size_t& row)const;
	bool isThereAccess(const size_t& x, const size_t& y);
	Point& preferNotInterfere(Board* b, vector<Block>& options)const;
	size_t oneToGoRowsCounter()const;
	size_t holesCounter()const;

	
	

public:
	void setSeparators(uint const& row);
	Board() : Board({0, 0}, LENGTH, WIDTH) {}
	Board(const Point& _pos) : Board(_pos, LENGTH, WIDTH) {}
	Board(uint _len, uint _width) : Board({0, 0}, _len, _width) {}
	Board(const Point& _pos, uint _len, uint _width);
	~Board() = default;
	friend std::ostream& operator<<(std::ostream& out, const Board& board) { board.drawBoard(); return out; }
	Board& operator=(const Board& _board);
	void allocateSize();
	void initialEmptyCells();
	void setAllBoundaries();
	void freezeBlock(const Block& block);
	void resizeBoundaries(const int& x, const int& y);
	uint checkBoard();
	void cleanBoard();
	void fillAllBoard(const uchar& shape);
	const uint& getLength() const { return length; }
	const uint& getWidth() const { return width; }
	void explosion(const Block& block);
	bool clockwiseRotate(const Block* block)const;
	bool counterClockwiseRotate(const Block* block)const;
	bool moveLeft(const Block* block)const;
	bool moveRight(const Block* block)const;
	bool moveDown(const Block* block)const;
	Point findBestPos(Block* block, short& situations)const;
	bool rotateCheck(Block* block, const ushort& dir)const;
	void drawBoundaries()const;
	void setBoardPos(const Point& newPos);
	Point getPointByPosition(const Point& pos)const;
	void getIndexByPosition(const Point& pos, size_t& x, size_t& y)const;
	void drawBoard(const Color& color)const;
	size_t numOfFillCells()const;
	
	
};

#endif

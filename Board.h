/***************************************
	Header file for class "Board".
***************************************/
#ifndef _BOARD_H_
#define _BOARD_H_

#include "Public_const_and_structs.h"
#include "Block.h"
#include "Point.h"


class Board
{
	enum Boundaries
	{
		WALL = 186, FLOOR = 205, UP_LEFT = 201, UP_RIGHT = 187, DOWN_LEFT = 200,
		DOWN_RIGHT = 188, RIGHT_CONNECTOR = 185, LEFT_CONNECTOR = 204
	};

	static constexpr size_t LENGTH = 19, WIDTH = 14;
	static bool colorsMode;

protected:
	Point pos;
	size_t length, width;
	vector<vector<Cell>> board;
	Color color;

	friend class Player;
	friend class HumanPlayer;
	friend class ComputerPlayer;
	friend class Game;
	friend class Menu;

private:
	void assign(const Board& _board);
	bool isFullRow(const size_t& row, const size_t& start, const size_t& end)const;
	bool isEmptyRow(const size_t& row, const size_t& start, const size_t& end)const;
	void setTopBoundary();
	void setBottomBoundary();
	void setRightBoundary();
	void setLeftBoundary();
	size_t getTopRow()const;
	bool moveLeftAboveBoard(const Block* block)const;
	bool moveRightAboveBoard(const Block* block)const;
	bool rotateAboveBoard(const Block& temp)const;
	void DropBlock(Block& block)const;
	void drawFillCells()const;
	void drawEmptyCells()const;
	void deleteBlock(const Block& block);
	size_t damageCounter(const Block& block)const;
	bool isWellConnected(const size_t& x, const size_t& y);
	void dropFloatingBricks(const size_t& startX, const size_t& endX, const size_t& startY, const size_t& endY, const size_t& height);
	bool notDisturbing(const Block& block)const;
	bool isBlocksAccess(const Block& block, const size_t& row)const;
	size_t countEmptyCells(const size_t& row)const;
	vector<Point> getEmptyCellsInRow(const size_t& row)const;
	bool isThereAccess(const size_t& x, const size_t& y);
	size_t oneToGoRowsCounter()const;
	inline bool isBoundary(const size_t& x, const size_t& y)const;
		
protected:
		void drawBoard() const;

public:
	void setSeparators(uint const& row);
	Board() : Board({ 0, 0 }, LENGTH, WIDTH) {}
	Board(const Point& _pos) : Board(_pos, LENGTH, WIDTH) {}
	Board(uint _len, uint _width) : Board({ 0, 0 }, _len, _width) {}
	Board(const Point& _pos, const size_t& _len, const size_t& _width, const Color& _color = WHITE);
	virtual ~Board() = default;
	static void changeColorsMode();
	friend std::ostream& operator<<(std::ostream& out, const Board& board);
	Board& operator*() { return *this; }
	Board* operator->() { return this; }
	Board& operator=(const Board& _board);
	void setColor(const Color& _color) { color = _color; }
	const Point& getPos()const { return pos; }
	const size_t& getLength() const { return length; }
	const size_t& getWidth() const { return width; }
	void allocateSize();
	void initialEmptyCells();
	void setAllBoundaries();
	void freezeBlock(const Block& block);
	void resizeBoundaries(const size_t& x, const size_t& y);
	uint checkBoard(bool draw);
	void cleanBoard();
	void fillAllBoard(const uchar& shape);
	void explosion(const Block& block);
	bool clockwiseRotate(const Block* block)const;
	bool counterClockwiseRotate(const Block* block)const;
	bool moveLeft(const Block* block)const;
	bool moveRight(const Block* block)const;
	bool moveDown(const Block* block)const;
	bool rotateCheck(Block* block, const ushort& dir)const;
	void drawBoundaries()const;
	void drawBoundaries(const Color& _color)const;
	virtual void setPos(const Point& newPos);
	Point getPointByPosition(const Point& pos)const;
	void getIndexByPosition(const Point& pos, size_t& x, size_t& y)const;
	void drawBoard(const Color& _color)const;
	size_t numOfFillCells()const;
	void cleanArea(size_t startX, size_t endX, size_t startY, size_t endY);
};

#endif

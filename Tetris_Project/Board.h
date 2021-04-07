/***************************************
	Header file for class "Board".
***************************************/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>


#include "Block.h"
#include "Point.h"
#include "Public const and structs.h"

using namespace std;

struct Board
{
	
	Point pos;
	uint length, width;
	vector<vector<uchar>> board;
	vector<Block> blocks;

private:
	bool isFullRow(const uint& row);
	void dropRows(const uint& row);
	int isFigureInRow(Block& block, const uint& row)const;
	void dropBlocks(const uint& row);
	void setTopBoundary();
	void setBottomBoundary();
	void setRightBoundary();
	void setLeftBoundary();
	
public:
	Board() : Board({ 0,0 }, 0, 0) {}
	Board(const Point& _pos) : Board({ _pos }, BOARD_LENGTH, BOARD_WIDTH) {}
	Board(uint _len, uint _width) :Board({ 0,0 }, _len, _width) {}
	Board(const Point& _pos, uint _len, uint _width);
	~Board();
	void allocateSize();
	void initialEmptyCells();
	void drawBoard()const;
	void setAllBoundaries();
	void freezeBlock(Block& block);
	void resizeBoundaries(const uint& x, const uint& y);
	uint checkBoard();
	void cleanBoard();
	void drawBoundaries();
	void drawBlocksInBoard();
};

#endif



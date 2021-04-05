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
	unsigned int length, width;
	vector<vector<char>> board;
	vector<Block> blocks;

private:
	bool isFullRow(const int& row);
	void dropRows(const int& row);
	
	
public:
	Board() : Board({ 0,0 }, 0, 0) {}
	Board(Point _pos) : Board({ _pos }, BOARD_LENGTH, BOARD_WIDTH) {}
	Board(unsigned int _len, unsigned int _width) :Board({ 0,0 }, _len, _width) {}
	Board(Point _pos, unsigned int _len, unsigned int _width);
	~Board();
	void setPos(int x, int y) { setPos({ x,y }); }
	void setPos(Point _pos) { pos = _pos; }
	void setTopBoundary();
	void setBottomBoundary();
	void setRightBoundary();
	void setLeftBoundary();
	void setAllBoundaries();
	void drawBoard();
	void freezeBlock(Block& block);
	void allocateSize();
	void initialEmptyCells();
	void resizeBoundaries(const unsigned int& x, const unsigned int& y);
	int checkBoard();
	void cleanBoard();
	void drawBoundaries();
	void drawBlocksInBoard();
};

#endif



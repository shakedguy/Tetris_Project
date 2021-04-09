/***************************************
	Header file for class "Board".
***************************************/
#pragma once

#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>


#include "Block.h"
#include "Point.h"
#include "io_utils.h"
//#include "Public_const_and_structs.h"

using namespace std;

class Board
{
	
	Point pos;
	uint length, width;
	vector<vector<uchar>> board;
	vector<Block> blocks;
	
	friend class Player;
	friend class Menu;
	friend class Box;

private:
	bool isFullRow(const uint& row);
	void dropRows(const uint& row);
	int isFigureInRow(Block& block, const uint& row)const;
	void dropBlocks(const uint& row);
	void setTopBoundary();
	void setBottomBoundary();
	void setRightBoundary();
	void setLeftBoundary();
	void drawBoard()const;
	void setSeparators(uint const& row);
	
public:
	Board() : Board({ 0,0 }, 0, 0) {}
	Board(const Point& _pos) : Board({ _pos }, BOARD_LENGTH, BOARD_WIDTH) {}
	Board(uint _len, uint _width) :Board({ 0,0 }, _len, _width) {}
	Board(const Point& _pos, uint _len, uint _width);
	~Board();
	friend ostream& operator<<(ostream& out, const Board& board) { board.drawBoard(); return out; }
	void allocateSize();
	void initialEmptyCells();
	void setAllBoundaries();
	void freezeBlock(Block& block);
	void resizeBoundaries(const int& x, const int& y);
	uint checkBoard();
	void cleanBoard();
	void drawBoundaries();
	void drawBlocksInBoard();
	void fillAllBoard(const uchar& shape);
	const uint& getLength()const { return length; }
	const uint& getWidth()const { return width; }
};

#endif



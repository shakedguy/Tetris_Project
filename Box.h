/***************************************
	Header file for class "Box".
***************************************/
#ifndef _BOX_H_
#define _BOX_H_

#include "Public_const_and_structs.h"
#include "Files_Handler.h"
#include "Block.h"
#include "Board.h"
#include "Point.h"

class Box : public Board
{
	static constexpr size_t LENGTH = 8, WIDTH = 8, NUM_OF_BLOCKS = 2;
	
	array<Block, NUM_OF_BLOCKS> blocks;

	friend class Player;
	friend class Game;
	friend class FilePlayer;

private:
	void setBlocks();
	void drawBox() const;
public:

	Box() : Box({0, 0}) {}
	Box(const Point& _pos);
	~Box() = default;
	friend std::ostream& operator<<(std::ostream& out, const Box& _box) { _box.drawBox(); return out; }
	Box& operator=(const Box& _box);
	void clearBox();
	void setPos(const Point& _pos)override { Board::setPos(_pos);  setBlocks(); }
	void clearScreen()override;
	//void readBlocksFromFile(const ushort& playerNum, Files_Handler* file);
};

#endif

#include "FilePlayer.h"


FilePlayer::FilePlayer(const ushort& _playerNum, const Point& _boardPos,
	const Point& _boxPos, const size_t& cycle) : Player(_playerNum, _boardPos, _boxPos, cycle)
{
	name = (playerNum == 1) ? "Test 1" : "Test 2";
	initBornData(cycle);
}

void FilePlayer::initBornData(const size_t& cycle)
{
	getNewBlock();
	if (playerNum == 1)
		block->pos = { LEFT_BLOCK, BLOCKS_Y };
	else 
		block->pos = { RIGHT_BLOCK, BLOCKS_Y };

}


void FilePlayer::setDirection(const uchar& key, const size_t& cycle)
{
	short temp = movesFile->getData(cycle);
	if (temp == -1) 
		direction = DEFAULT;	
	else
		direction = temp;
}

FilePlayer::FilePlayer(const FilePlayer& _player, const size_t& cycle) :
	FilePlayer(_player.playerNum, _player.boardPos, _player.boxPos, cycle) {}



void FilePlayer::getNewBlock()
{
	short temp = blocksFile->getFirst();
	if (temp < 0)
		throw BlocksFileEndEx();
		
	if (temp != Block::TetrisParts::B)
	{
		try { block = new Block; }
		catch (const std::bad_alloc& e) { e.what(); throw; }
		getFromFile(*block);
	}
	else
	{
		try { block = new Bomb; }
		catch (const std::bad_alloc& e) { e.what(); throw; }
		short x = blocksFile->getData(NULL);
	}
	if (playerNum == 1)
		block->pos = { LEFT_BLOCK,BLOCKS_Y };
	else
		block->pos = { RIGHT_BLOCK,BLOCKS_Y };
}

void FilePlayer::getFromFile(Block& b)
{
	b.cleanPrint();
	b.cleanBlock();
	short temp = blocksFile->getData(NULL);
	if (temp < 0)
		throw BlocksFileEndEx();
	b.shapeNum = temp;
	b.setFigure();
}







#include "FilePlayer.h"


FilePlayer::FilePlayer(const ushort& _playerNum, const Point& _boardPos,
	const Point& _boxPos, const size_t& cycle) : Player(_playerNum, _boardPos, _boxPos),
	blocksFile(playerNum,Files_Handler::read),movesFile(playerNum, Files_Handler::read)
{
	name = (playerNum == 1) ? "Test 1" : "Test 2";
	block->cleanPrint();
	block->cleanBlock();
	block->shapeNum = blocksFile.getData(cycle);
	block->setFigure();
	for (Block& i : box.blocks)
	{
		i.cleanPrint();
		i.cleanBlock();
		i.shapeNum = blocksFile.getData(cycle);
		i.setFigure();
	}
}

void FilePlayer::setDirection(const uchar& key, const size_t& cycle)
{
	const short temp = movesFile.getData(cycle);
	if (temp == -1)
		throw EndOfFileEx();
	direction = temp;
}

FilePlayer::FilePlayer(const FilePlayer& _player, const size_t& cycle) :
	FilePlayer(_player.playerNum, _player.boardPos, _player.boxPos, cycle) {}



void FilePlayer::getNewBlock()
{
	delete block;
	try { block = new Block(box.blocks[0]); }
	catch (const std::bad_alloc& e) { e.what(); throw MyException(); }
	const Point temp = box.blocks[0].pos;
	box.blocks[0] = box.blocks[1];
	box.blocks[0].pos = temp;
	try { getFromFile(box.blocks[1]); }
	catch (EndOfFileEx& ex)
	{
		direction = ESC;
		throw ex;
	}
	if (playerNum == 1)
		block->pos = { LEFT_BLOCK,BLOCKS_Y };
	else
		block->pos = { RIGHT_BLOCK,BLOCKS_Y };
}

void FilePlayer::getFromFile(Block& block)
{
	short temp = blocksFile.getData(NULL);
	if(temp==-1)
		throw EndOfFileEx();
	block.cleanPrint();
	block.cleanBlock();
	block.shapeNum = temp;
	block.setFigure();

}







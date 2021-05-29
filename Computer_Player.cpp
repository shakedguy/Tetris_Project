#include "Computer_Player.h"


ComputerPlayer::ComputerPlayer(const ushort& _playerNum, const Point& _boardPos,
	const Point& _boxPos) :
	Player(_playerNum, _boardPos, _boxPos)
{
	directionCheck.fill(DEFAULT);
	name = (playerNum == 1) ? "Computer player 1" : "Computer player 2";
}

ComputerPlayer::ComputerPlayer(const ComputerPlayer& _player) :
	Player(_player.playerNum, _player.boardPos, _player.boxPos),
	clockwise(_player.clockwise), CounterClockwise(_player.CounterClockwise),
	steps(_player.steps), directionCheck(_player.directionCheck)
{
	name = (playerNum == 1) ? "Computer player 1" : "Computer player 2";
}


ushort ComputerPlayer::level = 0;

void ComputerPlayer::assign(const ComputerPlayer& _player)
{
	Player::operator=(_player);
	if (directionCheck.size() == _player.directionCheck.size())
		directionCheck = _player.directionCheck;
	else
		directionCheck.fill(DEFAULT);
}

ComputerPlayer& ComputerPlayer::operator=(const ComputerPlayer& _player)
{
	if(this!=&_player)
	{
	     Player::operator=(_player);
	     steps = _player.steps;
		 clockwise = _player.clockwise;
	     CounterClockwise = _player.CounterClockwise;
	     if(directionCheck.size()==_player.directionCheck.size())
	     {
	          for (size_t i = 0; i < directionCheck.size(); ++i)
	               directionCheck[i] = _player.directionCheck[i];
	     }
	}
	return *this;
}


// If the block's position is at the originally started position - calls to the calculation function.
// Other - prefers sideways movement over rotation
void ComputerPlayer::setDirection(const uchar& key, const size_t& cycle)
{
	if (block->pos == Point{ Player::LEFT_BLOCK, BLOCKS_Y } ||
		block->pos == Point{ Player::RIGHT_BLOCK, BLOCKS_Y })
		calculateBestPos();
	if (!steps && (!clockwise || !CounterClockwise))
		direction = DEFAULT;
	else if (steps > 0 && board.moveRight(block))
		moveRight();
	else if (steps < 0 && board.moveLeft(block))
		moveLeft();
	else
		makeRotateMove();
	showIndicateHit(direction);
	insertCurrentDirection();
}

// If right shift is allow - execute and fixes steps 
void ComputerPlayer::moveRight()
{
	if (checkLastDirections(MOVE_RIGHT))
	{
		direction = MOVE_RIGHT;
		steps--;
	}
	else
		direction = DEFAULT;
}

// If left shift is allow - execute and fixes steps 
void ComputerPlayer::moveLeft()
{
	if (checkLastDirections(MOVE_LEFT))
	{
		direction = MOVE_LEFT;
		steps++;
	}
	else
		direction = DEFAULT;
}

// If clockwise Rotate is allow - execute and fixes steps 
void ComputerPlayer::clockwiseRotate()
{
	if (checkLastDirections(CLOCKWISE))
		direction = CLOCKWISE;
	else
		direction = DEFAULT;
	calculateRotates(block->shapeNum);
}

// If counter clockwise rotate is allow - execute and fixes steps 
void ComputerPlayer::counterClockwiseRotate()
{
	if (checkLastDirections(COUNTER_CLOCKWISE))
		direction = COUNTER_CLOCKWISE;
	else
		direction = DEFAULT;
	calculateRotates(block->shapeNum);
}

void ComputerPlayer::makeRotateMove()
{
	if (clockwise <= CounterClockwise && Player::board.clockwiseRotate(Player::block))
		clockwiseRotate();
	else if (Player::board.counterClockwiseRotate(Player::block))
		counterClockwiseRotate();
}

void ComputerPlayer::calculateRotates(const ushort& shape)
{
	if (shape == Block::L || shape == Block::J || shape == Block::T)
	{
		if (direction == CLOCKWISE)
		{
			--clockwise;
			CounterClockwise = 4 - clockwise;
		}
		else
		{
			--CounterClockwise;
			clockwise = 4 - CounterClockwise;
		}
	}
	else
	{
		clockwise--;
		CounterClockwise--;
	}
}

bool ComputerPlayer::checkLastDirections(const ushort& dir)
{
	for (const ushort& i : directionCheck)
		if (i != dir)
			return true;
	return false;
}

void ComputerPlayer::insertCurrentDirection()
{
	for (size_t i = 0; i < directionCheck.size() - 1; ++i)
		directionCheck[i + 1] = directionCheck[i];
	directionCheck[0] = direction;
}

// Checks the type the shape and sends to the correct
// calculation function according to the number of rotates it can do 
void ComputerPlayer::calculateBestPos()
{
	Point bestPos;
	const ushort& shape = Player::block->shapeNum;
	if (shape == Block::O)
		bestPos = noRotateBlock();
	if (shape == Block::I || shape == Block::S || shape == Block::Z)
		bestPos = oneRotateBlock();
	if (shape == Block::L || shape == Block::J || shape == Block::T)
		bestPos=threeRotateBlock();
	if (typeid(*block) == typeid(Bomb))
		bestPos = bomb();

	checkLevel(bestPos);
	steps = bestPos.getX() - Player::block->pos.getX();
}

void ComputerPlayer::checkLevel(Point& bestPos)const
{
	const std::uniform_int_distribution<> widthRange(1, Board::WIDTH - 2);
	std::random_device rnd;
	if (level == GOOD)
		levelGood(bestPos);
	else if (level == NOVICE)
		levelNovice(bestPos);
}

void ComputerPlayer::levelGood(Point& bestPos) const
{
	std::random_device rnd;
	const std::uniform_int_distribution<> widthRange(1, Board::WIDTH - 2);
	const std::uniform_int_distribution<> missRange(0, 39);
	if (typeid(*block) == typeid(Bomb))
		bestPos.setX(board.pos.getX() + widthRange(rnd));
	else if (!missRange(rnd))
	{

		int x = widthRange(rnd);
		while ((board.pos.getX() + x != bestPos.getX())) { x = widthRange(rnd); }
		bestPos.setX(board.pos.getX() + x);
	}
}

void ComputerPlayer::levelNovice(Point& bestPos) const
{
	std::random_device rnd;
	const std::uniform_int_distribution<> widthRange(1, Board::WIDTH - 2);
	const std::uniform_int_distribution<> missRange(0, 9);
	if (typeid(*block) == typeid(Bomb))
		bestPos.setX(board.pos.getX() + widthRange(rnd));
	else if (!missRange(rnd))
	{
		int x = widthRange(rnd);
		while ((board.pos.getX() + x != bestPos.getX())) { x = widthRange(rnd); }
		bestPos.setX(board.pos.getX() + x);
	} 
}

Point ComputerPlayer::noRotateBlock()
{
	ushort numOfRotates = 1;
	const Point& bestPos = findBestPosition(block, numOfRotates);
	clockwise = CounterClockwise = 0;
	return bestPos;
}

Point ComputerPlayer::oneRotateBlock()
{
	ushort numOfRotates = 2;
	const Point& bestPos = findBestPosition(block, numOfRotates);
	clockwise = CounterClockwise = numOfRotates;
	return bestPos;
}

Point ComputerPlayer::threeRotateBlock()
{
	ushort numOfRotates = 4;
	const Point& bestPos = findBestPosition(block, numOfRotates);
	clockwise = numOfRotates;
	CounterClockwise = 4 - clockwise;
	return bestPos;
}

Point ComputerPlayer::bomb()
{
	ushort numOfRotates = 1;
	const Point& bestPos = findBestPosition(block, numOfRotates);
	clockwise = CounterClockwise = 0;
	return bestPos;
}


/*
* Prefers the position that fills the most rows,
* If there are several equal, choose the lowest of them,
* If there is no position that fills rows,
* Takes the lowest positions and chooses among them those that complete a row for one to fill,
* then for those that do not interfere (create holes) in the rows below them 
*/
Point ComputerPlayer::findBestPosition(Block* block, ushort& situations)
{
	Board* b;
	Block* temp;
	try 
	{
		b = new Board(board);
		temp = new Block(*block);
	}
	catch (const std::bad_alloc& e) { e.what(); throw MyException(); }
	temp->pos = board.pos;
	if (typeid(*block) == typeid(Bomb))
		return findBestBombPosition(b, temp);

	list<pair<Block, ushort>> options(0);
	ushort bestSituation = situations;
	size_t fullRows = 0, maxFullRows = 0;
	Point lowestPos = block->pos, bestPos = block->pos;
	for (ushort i = 0; i < situations; ++i)
	{
		size_t limit = setLimit(temp);
		for (size_t j = 1; j < limit && b->moveRight(temp); ++j)
		{
			temp->pos >>= 1;
			fullRows = getPositionData(b, temp);
			checkFillRows(*temp, bestPos, fullRows, maxFullRows, i,bestSituation);
			if (!maxFullRows)
				checkLowest(options, *temp, lowestPos, i);
			b->deleteBlock(*temp);
			temp->pos.setY(b->pos.getY());
		}
		temp->pos = b->pos;
		temp->clockwiseRotate();
	}
	if (!maxFullRows)
		bestPos = checkOneToGo(b, options, bestSituation, lowestPos);
	if (bestPos == Point{ -1,-1 })
		bestPos = preferNotInterfere(b, options, bestSituation, lowestPos);
	situations = bestSituation;
	cleanAndDeleteCalculation(b, temp);
	return bestPos;
}

Point ComputerPlayer::findBestBombPosition(Board* b, Block* temp)const
{
	Point bestPos = temp->pos;
	size_t explosionCounter;
	size_t max = explosionCounter = 0;

	for (size_t j = 1; j < b->width - 1 && b->moveRight(temp); ++j)
	{
		temp->pos >>= 1;
		b->DropBlock(*temp);
		explosionCounter = b->damageCounter(*temp);
		bestPos = getMaxDamagedPosition(max, explosionCounter, bestPos, temp->pos);
		b->deleteBlock(*temp);
		temp->pos.setY(b->pos.getY());
	}
	cleanAndDeleteCalculation(b, temp);
	return bestPos;
}

size_t ComputerPlayer::getPositionData(Board* b, Block* temp) const
{
	temp->cleanPrint();
	b->DropBlock(*temp);
	b->freezeBlock(*temp);
	return b->checkBoard(false);
}

void ComputerPlayer::cleanAndDeleteCalculation(Board* b, Block* temp)const
{
	temp->cleanPrint();
	b->cleanBoard();
	delete temp;
	delete b;
}

Point ComputerPlayer::getMaxDamagedPosition(size_t& max, const size_t& current, const Point& bestPos,
	const Point& tempPos)const
{
	if (max > current)
		return bestPos;
	if (max == current && bestPos.compareY(tempPos) < 0)
		return tempPos;
	max = current;
	return tempPos;
}

size_t ComputerPlayer::setLimit(const Block* block)const
{
	size_t limit = board.width - 3;
	if (block->isColEmpty(Block::COLUMNS - 1) && block->isColEmpty(Block::COLUMNS - 2) && block->isColEmpty(Block::COLUMNS - 3))
		limit = board.width - 1;
	else if (block->isColEmpty(Block::COLUMNS - 1) && block->isColEmpty(Block::COLUMNS - 2))
		limit = board.width - 2;
	return limit;
}

Point ComputerPlayer::preferNotInterfere(Board* b, list<pair<Block, ushort>>& options,
	ushort& bestSituation, Point& lowestPos) const
{
	if(b->notDisturbing(options.back().first))
	{
		bestSituation = options.back().second;
		return options.back().first.pos;
	}
	Point& best = lowestPos;
	size_t i = 0;
	ushort s = bestSituation;
	bool flag = false;
	for (auto& cur : options)
	{
		if ((lowestPos.getY() - 2 <= cur.first.pos.getY()) &&
			b->notDisturbing(cur.first))
		{
			
			flag = true;
			best = cur.first.pos;
			s = cur.second;
		}
	}
	if (flag)
	{
		bestSituation = s;
		return best;
	}
	return lowestPos;
}

void ComputerPlayer::checkFillRows(const Block& temp, Point& bestPos, size_t& fullRows, size_t& maxFullRows,
	const ushort& situation, ushort& bestSituation)
{
	if (fullRows > maxFullRows)
	{
		maxFullRows = fullRows;
		bestPos = temp.pos;
		bestSituation = situation;

	}
	if (fullRows == maxFullRows && bestPos.compareY(temp.pos) > 0)
	{
		bestPos = temp.pos;
		bestSituation = situation;
	}
}

Point ComputerPlayer::checkOneToGo(Board* b, list<pair<Block, ushort>>& options,
	ushort& bestSituation, Point& lowestPos)const
{
	const size_t before = b->oneToGoRowsCounter();
	size_t max = before;
	Point best = lowestPos;
	bool flag = false;
	ushort situation = bestSituation;
	for(auto& cur:options)
	{
		if (lowestPos.getY() - 2 <= cur.first.pos.getY())
		{
			b->freezeBlock(cur.first);
			size_t current = b->oneToGoRowsCounter();
			if (max < current)
			{
				flag = true;
				max = current;
				best = cur.first.pos;
				situation = cur.second;
			}
			b->deleteBlock(cur.first);
		}
	}
	if (flag)
	{
		bestSituation = situation;
		return best;
	}
	bestSituation = options.front().second;
	return { -1,-1 };
}

void ComputerPlayer::checkLowest(list<pair<Block, ushort>>& options, const Block& temp,
	Point& lowestPos, const ushort& situation)
{
	if (lowestPos.compareY(temp.pos) > 0)	
	{
		lowestPos = temp.pos;
		options.push_back({ temp,situation });
	}
	else if (options.back().first.pos.getY() + options.back().first.getLowestRow() 
		< temp.pos.getY() + temp.getLowestRow())
		options.push_back({ temp,situation });
}

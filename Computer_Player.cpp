#include "Computer_Player.h"


ComputerPlayer::ComputerPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos) {

	Player::playerNum = _playerNum;
	Player::setBoardPos(_boardPos);
	Player::setBoxPos(_boxPos);
	box.setAllBoundaries();

	Player::direction = DEFAULT;
	score = 0;
	if (playerNum == 1) {
		block->pos = { LEFT_BLOCK, BLOCKS_Y };
		name = "Computer 1";
	}
	else {
		block->pos = { RIGHT_BLOCK, BLOCKS_Y };
		name = "Computer 2";
	}
	for (ushort& i : directionCheck)
		i = DEFAULT;

	Player::setGameBoundaries();
	Player::setKeysIndication();
}

ushort ComputerPlayer::level = 0;

ComputerPlayer& ComputerPlayer::operator=(const ComputerPlayer& _player)
{
	if(this!=&_player)
	{
	     Player::operator=(_player);
	     steps = _player.steps;
	     clockWise = _player.clockWise;
	     CounterClockWise = _player.clockWise;
	     if(directionCheck.size()==_player.directionCheck.size())
	     {
	          for (size_t i = 0; i < directionCheck.size(); ++i)
	               directionCheck[i] = _player.directionCheck[i];
	     }
	}
	return *this;
}


void ComputerPlayer::setDirection(const uchar& key)
{
	if (steps == INITIALIZE_STEPS && clockWise == INITIALIZE_ROTATES && CounterClockWise == INITIALIZE_ROTATES)
		calculateBestPos();
	if (!steps && (!clockWise || !CounterClockWise))
		direction = DEFAULT;
	else if (steps > 0 && board.moveRight(block))
	{
		if (checkLastDirections(MOVE_RIGHT))
		{
			direction = MOVE_RIGHT;
			steps--;
		}
		else
			direction = DEFAULT;
	}
	else if (steps < 0 && board.moveLeft(block))
	{
		if(checkLastDirections(MOVE_LEFT))
		{
		     direction = MOVE_LEFT;
		     steps++;
		}
		else
			direction = DEFAULT;
	}
	else
		makeRotateMove();
	showIndicateHit(direction);
	insertCurrentDirection();
}

void ComputerPlayer::makeRotateMove()
{
	const ushort& shape = Player::block->shapeNum;
	if (clockWise <= CounterClockWise && Player::board.clockwiseRotate(Player::block))
	{
		if (checkLastDirections(CLOCKWISE))
			direction = CLOCKWISE;
		else
			direction = DEFAULT;
	}
		
	else if (Player::board.counterClockwiseRotate(Player::block))
	{
		if (checkLastDirections(COUNTER_CLOCKWISE))
			direction = COUNTER_CLOCKWISE;
		else
			direction = DEFAULT;
	}
	else
		direction = DEFAULT;

	if (direction != DEFAULT)
	{
		if (shape == Block::L || shape == Block::J || shape == Block::T)
		{
			if (direction == CLOCKWISE)
				clockWise--;
			else
				clockWise++;
			CounterClockWise = 4 - clockWise;
		}
		else
		{
			clockWise--;
			CounterClockWise--;
		}
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
	clockWise = CounterClockWise = 0;
	return bestPos;
}

Point ComputerPlayer::oneRotateBlock()
{
	ushort numOfRotates = 2;
	const Point& bestPos = findBestPosition(block, numOfRotates);
	clockWise = CounterClockWise = numOfRotates;
	return bestPos;
}

Point ComputerPlayer::threeRotateBlock()
{
	ushort numOfRotates = 4;
	const Point& bestPos = findBestPosition(block, numOfRotates);
	clockWise = numOfRotates;
	CounterClockWise = 4 - clockWise;
	return bestPos;
}

Point ComputerPlayer::bomb()
{
	ushort numOfRotates = 1;
	const Point& bestPos = findBestPosition(block, numOfRotates);
	clockWise = CounterClockWise = 0;
	return bestPos;
}


Point ComputerPlayer::findBestPosition(Block* block, ushort& situations)
{

	Board* b = new Board;
	Block* temp = new Block;
	*b = board;
	*temp = *block;
	temp->pos = board.pos;
	if (typeid(*block) == typeid(Bomb))
		return findBestBombPosition(b, temp);

	vector<Block> options;
	vector<ushort> optionStatus;
	options.push_back(*block);
	optionStatus.push_back(0);
	ushort bestSituation = situations;
	size_t maxFullRows, fullRows, oneToGo;
	size_t maxOneToGo = oneToGo = fullRows = maxFullRows = 0;
	Point bestPos, lowestPos;
	Point oneToGoPos = lowestPos = bestPos = block->pos;
	bool flag = false;
	for (short i = 0; i < situations; ++i)
	{
		size_t limit = setLimit(temp);
		for (size_t j = 1; j < limit && b->moveRight(temp); ++j)
		{
			temp->pos >>= 1;
			fullRows = getPositionData(b, temp, oneToGo);
			checkFillRows(*temp, bestPos, fullRows, maxFullRows, bestSituation, i);
			if (!maxFullRows)
			{
				checkOneToGo(b, *temp, lowestPos, oneToGoPos, oneToGo, maxOneToGo, bestSituation, i, flag);
			     checkLowest(options, optionStatus, *temp, lowestPos, i);
			}
			b->deleteBlock(*temp);
			temp->pos.setY(b->pos.getY());
		}
		temp->pos = b->pos;
		temp->clockwiseRotate();
	}

	if (!maxFullRows && !flag)
		bestSituation = preferNotInterfere(b, options, optionStatus, bestPos);
	else if (flag)
		bestPos = oneToGoPos;
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

size_t ComputerPlayer::getPositionData(Board* b, Block* temp, size_t& oneToGo) const
{
	temp->cleanPrint();
	oneToGo = b->oneToGoRowsCounter();
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

Point ComputerPlayer::getMaxDamagedPosition(size_t& max, const size_t& current, const Point& bestPos, const Point& tempPos)const
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

const short& ComputerPlayer::preferNotInterfere(Board* b, vector<Block>& options, vector<ushort>& optionStatus, Point& bestPos) const
{
	bestPos = options.back().pos;
	int i = options.size() - 1;
	while (i >= 0)
	{
		if (b->notDisturbing(options[i]) && options[i].pos.getY() >= bestPos.getY() - 4)
		{
			bestPos = options[i].pos;
			return optionStatus[i];
		}
		--i;
	}
	Block temp = options.back();
	for (size_t i = 0; i < options.size(); ++i)
	{
		if (options[i].pos.compareY(bestPos) == 0 && options[i].getLowestRow() >= temp.getLowestRow())
		{
			bestPos = options[i].pos;
			return optionStatus[i];
		}
	}
	bestPos = options[options.size() - 1].pos;
	return optionStatus[optionStatus.size() - 1];
}

void ComputerPlayer::checkFillRows(const Block& temp, Point& bestPos, size_t& fullRows, size_t& maxFullRows,
	ushort& bestSituation, const ushort& situation)
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

void ComputerPlayer::checkOneToGo(Board* b, const Block& temp, const Point& lowestPos, Point& oneToGoPos, size_t& oneToGo,
	size_t& maxOneToGo, ushort& bestSituation, const ushort& situation, bool& flag)
{

	const size_t after = b->oneToGoRowsCounter();
	if (oneToGo < after && maxOneToGo < after && b->notDisturbing(temp))
	{
		maxOneToGo = after;
		oneToGoPos = temp.pos;
		bestSituation = situation;
		flag = true;
	}
}

void ComputerPlayer::checkLowest(vector<Block>& options, vector<ushort>& optionStatus, const Block& temp,
	Point& lowestPos, const ushort& situation)
{
	if (lowestPos.compareY(temp.pos) > 0)
	{
		lowestPos = temp.pos;
		options.push_back(temp);
		optionStatus.push_back(situation);
	}
	if (lowestPos.compareY(temp.pos) == 0 && options.back().getLowestRow()<temp.getLowestRow())
	{
		lowestPos = temp.pos;
		options.push_back(temp);
		optionStatus.push_back(situation);
	}
}


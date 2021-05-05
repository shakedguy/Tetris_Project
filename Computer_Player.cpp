#include "Computer_Player.h"


ComputerPlayer::ComputerPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos) {

	Player::playerNum = _playerNum;
	Player::setBoardPos(_boardPos);
	Player::setBoxPos(_boxPos);

	Player::direction = DEFAULT;
	score = 0;
	if (playerNum == 1) {
		block->pos = { LEFT_BLOCK, BLOCKS_Y };
		name = "Computer 1";
	}
	else {
		block->pos = { RIGHT_BLOCK, BLOCKS_Y };
		name = "Computer";
	}
	for (ushort& i : directionCheck)
		i = DEFAULT;

	Player::setGameBoundaries();
	Player::setKeysIndication();
}

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
	steps = bestPos.getX() - Player::block->pos.getX();
}

Point ComputerPlayer::noRotateBlock()
{
	short numOfRotates = 1;
	const Point& bestPos = board.findBestPos(block, numOfRotates);
	clockWise = CounterClockWise = 0;
	return bestPos;
}

Point ComputerPlayer::oneRotateBlock()
{
	short numOfRotates = 2;
	const Point& bestPos = board.findBestPos(block, numOfRotates);
	clockWise = CounterClockWise = numOfRotates;
	return bestPos;
}

Point ComputerPlayer::threeRotateBlock()
{
	short numOfRotates = 4;
	const Point& bestPos = board.findBestPos(block, numOfRotates);
	clockWise = numOfRotates;
	CounterClockWise = 4 - clockWise;
	return bestPos;
}



Point ComputerPlayer::bomb()
{
	short numOfRotates = 1;
	const Point& bestPos = board.findBestPos(block, numOfRotates);
	clockWise = CounterClockWise = 0;
	return bestPos;
}

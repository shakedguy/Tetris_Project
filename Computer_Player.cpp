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

// Inserting characters and numbers into the step's representation map
void ComputerPlayer::setPlayerKeys(const string& arrowKeys) {

	for (sint i = 0; i < arrowKeys.size(); ++i) {

		keys.insert({ arrowKeys[i], i });
		if (arrowKeys[i] >= 'a')
			keys.insert({ arrowKeys[i] - ('a' - 'A'), i });
		else
			keys.insert({ arrowKeys[i] + ('a' - 'A'), i });
	}
}

// Returns the number representing the step, if the character does not belong to the player's step characters, returns -1
sint ComputerPlayer::getDirection(const uchar& key) {

	auto find = keys.find(key);
	if (find != keys.end()) {
		Player::showIndicateHit(keys.at(find->first));
		return keys.at(find->first);
	}
	return -1;
}

// Gets a key and returns if it represents the DEFAULT direction
bool ComputerPlayer::isDown(const uchar& key) {

	if (keys[key] == DEFAULT)
		return true;
	return false;
}

// Gets a direction and returns the characters representation, if its the DEFAULT direction, returns 0
uchar ComputerPlayer::getKey(const ushort& dir) const {

	for (auto const& pair : keys)
		if (dir == pair.second)
			return pair.first;
	return 0;
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

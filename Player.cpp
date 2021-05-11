#include "Player.h"


bool Player::colorsMode = false;

Player& Player::operator=(const Player& _player)
{

	if (this != &_player)
	{
		name = _player.name;
		playerNum = _player.playerNum;
		direction = _player.direction;
		boardPos = _player.boardPos;
		boxPos = _player.boxPos;
		board = _player.board;
		box = _player.box;
		*block = *_player.block;
		score = _player.score;
		if (keyIndicators.size() == _player.keyIndicators.size())
			keyIndicators = _player.keyIndicators;
	}
	return *this;
}


std::ostream& operator<<(std::ostream& out, const Player* _player) {
	
	cout << _player->board << _player->box << *_player->block;
	_player->drawKeysIndication();
	return out;
}

// Sets the map of keys indicators
void Player::setKeysIndication() {
	
	for (auto i = 0; i < keyIndicators.size(); ++i) {

		keyIndicators[i].resizeBoundaries(INDIVATORS_WIDTH, INDIVATORS_LENGTH);

		if (i < keyIndicators.size() - 2)
			keyIndicators[i].setBoardPos({ boardPos.getX() + 4, boardPos.getY() + Board::LENGTH + (i * INDIVATORS_LENGTH) });
		else if (i == keyIndicators.size() - 2)
			keyIndicators[i].setBoardPos({
			keyIndicators[1].pos.getX() - static_cast<int>(keyIndicators[1].width), keyIndicators[1].pos.getY() });
		else if (i == keyIndicators.size() - 1)
			keyIndicators[i].setBoardPos({
		     static_cast<int>(keyIndicators[1].width) + keyIndicators[1].pos.getX(), keyIndicators[1].pos.getY() });
		keyIndicators[i].initialEmptyCells();
		keyIndicators[i].setAllBoundaries();
	}
}

void Player::drawKeysIndication() const {

	for (const Board& indicator : keyIndicators)
		cout << indicator;
}

void Player::clearGame() {
	
	board.cleanBoard();
	box.clearBox();
	block->createNewBlock();
	setGameBoundaries();
	if (playerNum == 1)
		block->pos = {LEFT_BLOCK, BLOCKS_Y};
	else
		block->pos = {RIGHT_BLOCK,BLOCKS_Y};
}

// Remove the top boundary of the board
void Player::setGameBoundaries() {
	
	board.setAllBoundaries();
	board.cleanArea(0, board.width-1, 0, 0);
}

// check if the player losed
bool Player::isLost() {
	for (size_t i = 1; i < board.width - 1; ++i)
		if (board.board[i][0].getShape() != EMPTY_CELL)
			return true;
	return false;
}

void Player::printScore() const {
	
	if (Player::colorsMode)
		setTextColor(LIGHTCYAN);

	Point pos;
	if (playerNum == 1)
		pos = {LEFT_SCORE,SCORES_Y};
	else
		pos = { RIGHT_SCORE,SCORES_Y };
	gotoxy(pos.getX(), pos.getY());
	cout << name;
	gotoxy(pos.getX(), pos.getY() + 1);
	cout << "score: ";
	gotoxy(pos.getX() + 2, pos.getY() + 2);
	cout << score;

	if (Player::colorsMode)
		setTextColor(WHITE);
}

// Draw an indication of a step click
void Player::showIndicateHit(const ushort& dir) {

	drawKeysIndication();
	if(dir!=DEFAULT)
	{
	     if (Player::colorsMode)
	          keyIndicators[dir].drawBoard(RED);
	     else {
	          keyIndicators[dir].fillAllBoard('#');
	          cout << keyIndicators[dir];
	          keyIndicators[dir].setAllBoundaries();
	     }
	}
}

// Takes the first block from the box and put it in the "current block", put the second instead of the first and
// get new block to the second
void Player::getNewBlock() {

	delete block;
	std::random_device bombChances;
	const std::uniform_int_distribution<> rnd(0, 19);
	if (rnd(bombChances))
	{
		block = new Block();
		*block = box.blocks[0];
		const Point temp = box.blocks[0].pos;
		box.blocks[0] = box.blocks[1];
		box.blocks[0].pos = temp;
		box.blocks[1].createNewBlock();
	}
	else
		block = new Bomb();
	initializeCalculate();

	if (playerNum == 1)
		block->pos = { LEFT_BLOCK,BLOCKS_Y };
	else
		block->pos = { RIGHT_BLOCK,BLOCKS_Y };
}

/* Player move function, if the step faild and the direction is DEFAULT,
 * "freeze" the block and insert it to the board's blocks and brings a new block to the playing field,
 * update the score and the returns the direction to DEFAULT */
void Player::move() {

	if (!makeTheMove() && direction == DEFAULT) {

		if (typeid(*block) == typeid(Bomb))
			board.explosion(*block);
		else
		     board.freezeBlock(*block);

          getNewBlock();
		cout << board << box;
	}
	board.drawFillCells();
	board.drawBoundaries();
	score += ((pow(board.checkBoard(true), 2)) * POINTS_FOR_FULL_ROW);
	direction = DEFAULT;
}

/* Check the current direction and send to the step execution function,
 * returns if the step succeeded or failed */
bool Player::makeTheMove() {
	
	switch (direction) {
	case COUNTER_CLOCKWISE:
		return counterClockwise();
	case CLOCKWISE:
		return clockwise();
	case DROP:
		return drop();
	case MOVE_LEFT:
		return left();
	case MOVE_RIGHT:
		return right();
	default:
		return down();
	}
}

bool Player::clockwise()
{
	direction = DEFAULT;
	if (typeid(*block) == typeid(Bomb) || block->shapeNum == Block::O)
		return makeTheMove();
	if (board.rotateCheck(block, CLOCKWISE))
	{
		block->clockwiseRotate();
		return true;
	}
	return makeTheMove();
}

bool Player::counterClockwise()
{
	direction = DEFAULT;
	if (typeid(*block) == typeid(Bomb) || block->shapeNum == Block::O)
		return makeTheMove();
	if (board.rotateCheck(block, COUNTER_CLOCKWISE))
	{
		block->counterClockwiseRotate();
		return true;
	}
	return makeTheMove();
}

bool Player::down()
{
	if (board.moveDown(block))
	{
		block->moveDown();
		return true;
	}
	return false;
}

bool Player::left()
{
	if (board.moveLeft(block))
	{
		block->moveLeft();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove();
}

bool Player::right()
{
	if (board.moveRight(block))
	{
		block->moveRight();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove();
}

// Loop of moving the block down until it comes across another block or the board border
bool Player::drop() {

	while (board.moveDown(block))
		block->moveDown();
	direction = DEFAULT;
	return false;
}

void Player::changeColorsMode() {
	
	if (Player::colorsMode)
		Player::colorsMode = false;
	else
		Player::colorsMode = true;
}

// Check if game speed needs to be increased
bool Player::checkSpeed(const size_t& accNum)const {

	if (board.numOfFillCells() > accNum * CELLS_FOR_ACCELERATION || score > accNum * SCORE_FOR_ACCELERATION)
		return true;
	return false;
}



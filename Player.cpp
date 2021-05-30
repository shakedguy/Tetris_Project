#include "Player.h"

#include "Game.h"



Player::Player(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos) :
	playerNum(_playerNum), direction(DEFAULT), boardPos(_boardPos),
	boxPos(_boxPos), board(boardPos), box(boxPos)
{
	if (playerNum == 1)
	{
		name = "Player 1";
		try { block = new Block({ LEFT_BLOCK, BLOCKS_Y }); }
		catch (const std::bad_alloc& e) { e.what(); throw MyException(); }
	}
	else
	{
		name = "Player 2";
		try { block = new Block({ RIGHT_BLOCK, BLOCKS_Y }); }
		catch (const std::bad_alloc& e) { e.what(); throw MyException(); }
	}

	setGameBoundaries();
	setKeysIndication();

	if (Player::gameMode != Player::SIMPLE)
		initFiles();
}

void Player::initFiles()
{
	if (Player::gameMode != Player::SAVE)
		allocateToRead();
	else
	{
		allocateToWrite();
		blocksFile->saveData(block->shapeNum, NULL, NULL);
	}
}

void Player::allocateToWrite() noexcept(false)
{
	try
	{
		blocksFile = new Blocks_Files(playerNum, Files_Handler::write);
		movesFile = new Moves_Files(playerNum, Files_Handler::write);
	}
	catch (const std::bad_alloc& e)
	{
		e.what();
		throw;
	}
}

void Player::allocateToRead()noexcept(false)
{
	try
	{
		blocksFile = new Blocks_Files(playerNum, Files_Handler::read);
		movesFile = new Moves_Files(playerNum, Files_Handler::read);
	}
	catch (const std::bad_alloc& e)
	{
		e.what();
		throw;
	}
}


Player::Player(const Player& _player) :
	Player(_player.playerNum, _player.boardPos, _player.boxPos) {}

Player::~Player()
{
	delete block;
	delete blocksFile;
	delete movesFile;
}

void Player::printDataToFile()const
{
	blocksFile->print();
	movesFile->print();
}


bool Player::colorsMode = false;
ushort Player::gameMode = 0;

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

void Player::resetCurrentBlocksPos()const
{
	if (playerNum == 1)
		block->pos = { Player::LEFT_BLOCK, Player::BLOCKS_Y };
	else
		block->pos = { Player::RIGHT_BLOCK,Player::BLOCKS_Y };

}


// Sets the map of keys indicators
void Player::setKeysIndication() {

	size_t count = 0;
	for (Board& i : keyIndicators)
	{
		i.resizeBoundaries(INDIVATORS_WIDTH, INDIVATORS_LENGTH);
		if (count < keyIndicators.size() - 2)
			i.setPos(Point{boardPos.getX() + 4,
				count * INDIVATORS_LENGTH + boardPos.getY() + Board::LENGTH});
		else if (count == keyIndicators.size() - 2)
			i.setPos(Point{ keyIndicators[1].pos.getX() - keyIndicators[1].width,
				static_cast<size_t>(keyIndicators[1].pos.getY()) });
		else if (count == keyIndicators.size() - 1)
			i.setPos(Point{ keyIndicators[1].width + keyIndicators[1].pos.getX(),
				keyIndicators[1].pos.getY() });
		i.initialEmptyCells();
		i.setAllBoundaries();
		i.setColor(RED);
		++count;
	}
}

void Player::drawKeysIndication() const {

	if(Player::gameMode != Player::LOAD && Player::gameMode != Player::SILENT)
	{
		for (const Board& indicator : keyIndicators)
			indicator.drawBoard(WHITE);
	}
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
	
	if (Player::gameMode == SAVE)
		clearFilesContent();	
}

void Player::clearFilesContent()
{
	blocksFile->clearGame();
	movesFile->clearGame();
}


// Remove the top boundary of the board
void Player::setGameBoundaries()
{
	
	board.setAllBoundaries();
	board.cleanArea(0, board.width-1, 0, 0);
}

// check if the player losed
bool Player::isLost()
{
	for (size_t i = 1; i < board.width - 1; ++i)
		if (board.board[i][0].getShape() != EMPTY_CELL)
			return true;
	return false;
}

void Player::printScore() const
{
	
	if (Player::colorsMode)
		setTextColor(LIGHTCYAN);

	Point pos;
	if (playerNum == 1)
		pos = {LEFT_SCORE,SCORES_Y};
	else
		pos = { RIGHT_SCORE,SCORES_Y };
	if (this->type() == Player::COMPUTER && playerNum == 1)
		pos <<= 6;
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
			cout << keyIndicators[dir];
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
		try { block = new Block(); }
		catch (const std::bad_alloc& e) { e.what(); throw MyException(); }
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
	if (Player::gameMode == Player::SAVE)
		blocksFile->saveData(block->shapeNum, NULL, NULL);
}

/* Player shift function, if the step faild and the direction is DEFAULT,
 * "freeze" the block and insert it to the board's blocks and brings a new block to the playing field,
 * update the score and the returns the direction to DEFAULT */
void Player::move(const size_t& cycle) {

	if (!makeTheMove(cycle) && direction == DEFAULT) {

		if (typeid(*block) == typeid(Bomb))
			board.explosion(*block);
		else
			board.freezeBlock(*block);
		
		try { getNewBlock(); }
		catch (...) { throw; }
		
		cout << box;
		board.drawEmptyCells();

	}
	board.drawFillCells();
	board.drawBoundaries();
	score += ((pow(board.checkBoard(true), 2)) * POINTS_FOR_FULL_ROW);
}


/* Check the current direction and send to the step execution function,
 * returns if the step succeeded or failed */
bool Player::makeTheMove(const size_t& cycle) {
	
	switch (direction) {
	case COUNTER_CLOCKWISE:
		return counterClockwise(cycle);
	case CLOCKWISE:
		return clockwise(cycle);
	case DROP:
		return drop(cycle);
	case MOVE_LEFT:
		return left(cycle);
	case MOVE_RIGHT:
		return right(cycle);
	default:
		return down(cycle);
	}
}

bool Player::clockwise(const size_t& cycle)
{
	direction = DEFAULT;
	if (typeid(*block) == typeid(Bomb) || block->shapeNum == Block::O)
		return makeTheMove(cycle);
	if (board.rotateCheck(block, CLOCKWISE))
	{
		movesFile->saveData(NULL, cycle, CLOCKWISE);
		block->clockwiseRotate();
		return true;
	}
	return makeTheMove(cycle);
}

bool Player::counterClockwise(const size_t& cycle)
{
	direction = DEFAULT;
	if (typeid(*block) == typeid(Bomb) || block->shapeNum == Block::O)
		return makeTheMove(cycle);
	if (board.rotateCheck(block, COUNTER_CLOCKWISE))
	{
		movesFile->saveData(NULL, cycle, COUNTER_CLOCKWISE);
		block->counterClockwiseRotate();
		return true;
	}
	return makeTheMove(cycle);
}

bool Player::down(const size_t& cycle)
{
	if (board.moveDown(block))
	{
		movesFile->saveData(NULL, cycle, DEFAULT);
		block->moveDown();
		return true;
	}
	return false;
}

bool Player::left(const size_t& cycle)
{
	if (board.moveLeft(block))
	{
		movesFile->saveData(NULL, cycle, MOVE_LEFT);
		block->moveLeft();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove(cycle);
}

bool Player::right(const size_t& cycle)
{
	if (board.moveRight(block))
	{
		movesFile->saveData(NULL, cycle, MOVE_RIGHT);
		block->moveRight();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove(cycle);
}

// Loop of moving the block down until it comes across another block or the board border
bool Player::drop(const size_t& cycle) {

	while (board.moveDown(block))
	{
		movesFile->saveData(NULL, cycle, DROP);
		block->moveDown();
	}
	direction = DEFAULT;
	return false;
}

void Player::changeColorsMode()
{
	
	if (Player::colorsMode)
		Player::colorsMode = false;
	else
		Player::colorsMode = true;
}

// Check if game speed needs to be increased
bool Player::checkSpeed(const size_t& accNum)const
{
	if (board.numOfFillCells() > accNum * CELLS_FOR_ACCELERATION || score > accNum * SCORE_FOR_ACCELERATION)
		return true;
	return false;
}

bool Player::isEndOfFiles() const
{
	if (blocksFile->isEmpty() && movesFile->isEmpty())
		return true;
	return false;
}




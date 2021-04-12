#include "Player.h"

Player::Player(ushort _playerNum, Point _boardPos, Point _boxPos) : playerNum(_playerNum),
																	boardPos(_boardPos),
																	boxPos(_boxPos),
																	board(boardPos, BOARD_LENGTH, BOARD_WIDTH),
																	box(boxPos) {
	direction = DEFAULT;
	score = 0;
	if (playerNum == 1) {
		block.pos = {LEFT_CURRENT_BLOCK};
		name = "Player 1";
	}
	else {
		block.pos = {RIGHT_CURRENT_BLOCK};
		name = "Player 2";
	}
	setGameBoundaries();
	setKeysIndication();
}

bool Player::colorsMode = false;

std::ostream& operator<<(std::ostream& out, const Player& _player) {
	
	cout << _player.board << _player.box << _player.block;
	_player.drawKeysIndication();
	return out;
}

// Sets the map of keys indicators
void Player::setKeysIndication() {
	
	for (auto i = 0; i < keyIndicators.size(); i++) {
		
		keyIndicators[i].resizeBoundaries(kEY_INDIVATORS_WIDTH, kEY_INDIVATORS_LENGTH);
		keyIndicators[i].setAllBoundaries();
		if (i < keyIndicators.size() - 2)
			keyIndicators[i].pos = {boardPos.getX() + 4, boardPos.getY() + BOARD_LENGTH + (i * kEY_INDIVATORS_LENGTH)};
	}
	keyIndicators[keyIndicators.size() - 2].pos = {
			keyIndicators[1].pos.getX() - static_cast<int>(keyIndicators[1].width), keyIndicators[1].pos.getY()};
	keyIndicators[keyIndicators.size() - 1].pos = {
			static_cast<int>(keyIndicators[1].width) + keyIndicators[1].pos.getX(), keyIndicators[1].pos.getY()};
}

void Player::drawKeysIndication() const {
	
	for (ushort i = 0; i < keyIndicators.size(); ++i) {
		cout << keyIndicators[i];
		gotoxy(keyIndicators[i].pos.getX() + 1, keyIndicators[i].pos.getY() + 1);
		cout << getKey(i);
	}
}

void Player::setName() {
	
	gotoxy(WINNING_MASSAGE);
	cout << "Please enter player " << playerNum << " name:  ";
	cin >> name;
	clrscr();
}

void Player::clearGame() {
	
	board.cleanBoard();
	box.clearBox();
	block.createNewBlock();
	setGameBoundaries();
	if (playerNum == 1)
		block.pos = {LEFT_CURRENT_BLOCK};
	else
		block.pos = {RIGHT_CURRENT_BLOCK};
}

// Remove the top boundary of the board
void Player::setGameBoundaries() {
	
	board.setAllBoundaries();
	for (size_t i = 0; i < board.width; ++i)
		board.board[i][0] = EMPTY_CELL;
}

// check if the player losed
bool Player::isLost() {
	for (uint i = 1; i < board.width - 1; ++i)
		if (board.board[i][1] != EMPTY_CELL)
			return true;
	return false;
}

void Player::printScore() const {
	
	if (Player::colorsMode)
		setTextColor(LIGHTCYAN);

	Point pos;
	if (playerNum == 1)
		pos = {LEFT_SCORE_POS};
	else
		pos = {RIGHT_SCORE_POS};
	gotoxy(pos.getX(), pos.getY());
	cout << name << "'s score: ";
	gotoxy(pos.getX() + 5, pos.getY() + 1);
	cout << score;

	if (Player::colorsMode)
		setTextColor(WHITE);
}

// Inserting characters and numbers into the step's representation map
void Player::setPlayerKeys(const string& arrowKeys) {
	
	for (sint i = 0; i < arrowKeys.size(); ++i) {
		
		keys.insert({arrowKeys[i], i});
		if (arrowKeys[i] >= 'a')
			keys.insert({arrowKeys[i] - ('a' - 'A'), i});
		else
			keys.insert({arrowKeys[i] + ('a' - 'A'), i});
	}
}

// Loop of moving the block down until it comes across another block or the board border
bool Player::drop() {
	
	while (moveDown()) {}
	direction = DEFAULT;
	return false;
}

// Returns the number representing the step, if the character does not belong to the player's step characters, returns -1
sint Player::getDirection(const uchar& key) {
	
	auto find = keys.find(key);
	if (find != keys.end()) {
		showIndicateHit(keys.at(find->first));
		return keys.at(find->first);
	}
	return -1;
}

// Draw an indication of a step click
void Player::showIndicateHit(const ushort& dir) {

	drawKeysIndication();
	if (Player::colorsMode) {
		setTextColor(RED);
		cout << keyIndicators[dir];
		gotoxy(keyIndicators[dir].pos.getX() + 1, keyIndicators[dir].pos.getY() + 1);
		setTextColor(WHITE);
		cout << getKey(dir);
	}
	else {
		keyIndicators[dir].fillAllBoard('#');
		cout << keyIndicators[dir];
		gotoxy(keyIndicators[dir].pos.getX() + 1, keyIndicators[dir].pos.getY() + 1);
		cout << getKey(dir);
		keyIndicators[dir].setAllBoundaries();
	}
}

void Player::cleanIndicatorsHit(const ushort& dir) {
	
	if (Player::colorsMode)
		setTextColor(WHITE);
	keyIndicators[dir].cleanBoard();
	keyIndicators[dir].setAllBoundaries();
	drawKeysIndication();
}

// Gets a key and returns if it represents the DEFAULT direction
bool Player::isDown(const uchar& key) {
	
	if (keys[key] == DEFAULT)
		return true;
	return false;
}

// Gets a direction and returns the characters representation, if its the DEFAULT direction, returns 0
const uchar& Player::getKey(const ushort& dir) const {
	
	for (auto const& pair : keys)
		if (dir == pair.second)
			return pair.first;
	return 0;
}

// Takes the first block from the box and put it in the "current block", put the second instead of the first and
// get new block to the second
void Player::getNewBlock() {
	
	block = box.blocks[0];
	if (playerNum == 1)
		block.pos = {LEFT_CURRENT_BLOCK};
	else
		block.pos = {RIGHT_CURRENT_BLOCK};
	const Point temp = box.blocks[0].pos;
	box.blocks[0] = box.blocks[1];
	box.blocks[0].pos = temp;
	box.blocks[1].createNewBlock();
}

/* Player move function, if the step faild and the direction is DEFAULT,
 * "freeze" the block and insert it to the board's blocks and brings a new block to the playing field,
 * update the score and the returns the direction to DEFAULT */
void Player::move() {
	
	if (!makeTheMove() && direction == DEFAULT) {
		board.freezeBlock(block);
		getNewBlock();
		cout << box;
		block.drawBlock();
	}
	board.drawBlocksInBoard();
	board.drawBoundaries();
	score += ((pow(board.checkBoard(), 2)) * POINTS_FOR_FULL_ROW);
	direction = DEFAULT;
}

/* Check the current direction and send to the step execution function,
 * returns if the step succeeded or failed */
bool Player::makeTheMove() {
	
	switch (direction) {
	case COUNTER_CLOCKWISE:
		return counterClockwiseRotate();
	case CLOCKWISE:
		return clockwiseRotate();
	case DROP:
		return drop();
	case MOVE_LEFT:
		return moveLeft();
	case MOVE_RIGHT:
		return moveRight();

	default:
		return moveDown();
	}
}

/* A function that checks if a down step is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Player::moveDown() {
	
	if (block.pos.getY() < board.pos.getY()) {
		block.moveDown();
		return true;
	}
	for (int i = 0; i < block.figure.size(); i++) {
		for (int j = 0; j < block.figure[i].size(); j++) {
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i - boardPos.getX()][block.pos.getY() + j + 1 - boardPos.getY()] != ' ')
			)
				return false;
		}
	}
	block.moveDown();
	return true;
}

/* A function that checks if a left step is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Player::moveLeft() {
	
	if (block.pos.getY() < board.pos.getY())
		return moveLeftAboveBoard();
	for (int i = 0; i < block.figure.size(); i++) {
		for (int j = 0; j < block.figure[i].size(); j++) {
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i - 1 - boardPos.getX()][block.pos.getY() + j - boardPos.getY()]
					!= EMPTY_CELL)) {
				direction = DEFAULT;
				return makeTheMove();
			}
		}
	}
	block.moveLeft();
	return true;
}

bool Player::moveLeftAboveBoard() {
	
	if (block.pos.getX() > board.pos.getX() + 1) {
		block.moveLeft();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove();
}

/* A function that checks if a right step is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Player::moveRight() {
	
	if (block.pos.getY() < board.pos.getY())
		return moveRightAboveBoard();
	for (int i = 0; i < block.figure.size(); i++) {
		for (int j = 0; j < block.figure[i].size(); j++) {
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i + 1 - boardPos.getX()][block.pos.getY() + j - boardPos.getY()]
					!= EMPTY_CELL)) {
				direction = DEFAULT;
				return makeTheMove();
			}
		}
	}
	block.moveRight();
	return true;
}

bool Player::moveRightAboveBoard() {
	
	if (block.pos.getX() + block.figure.size() < board.pos.getX() + board.board.size() - 1) {
		block.moveRight();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove();
}

/* A function that checks if a clockwise rotate is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Player::clockwiseRotate() {
	
	Block temp = block;
	temp.clockwiseRotate();
	if (block.pos.getY() < board.pos.getY())
		return rotateAboveBoard(temp);
	for (int i = 0; i < block.figure.size(); i++) {
		for (int j = 0; j < block.figure[i].size(); j++) {
			if (temp.figure[i][j] &&
				(board.board[temp.pos.getX() + i - boardPos.getX()][temp.pos.getY() + j - boardPos.getY()] != EMPTY_CELL
				))
				return moveDown();

		}
	}
	block.cleanPrint();
	block = temp;
	block.drawBlock();
	return true;
}

/* A function that checks if a counter clockwise rotate is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Player::counterClockwiseRotate() {

	Block temp = block;
	temp.counterClockwiseRotate();
	if (block.pos.getY() < board.pos.getY())
		return rotateAboveBoard(temp);
	for (int i = 0; i < block.figure.size(); i++) {
		for (int j = 0; j < block.figure[i].size(); j++) {
			if (temp.figure[i][j] &&
				(board.board[temp.pos.getX() + i - boardPos.getX()][temp.pos.getY() + j - boardPos.getY()] != EMPTY_CELL
					))
				return moveDown();

		}
	}
	block.cleanPrint();
	block = temp;
	block.drawBlock();
	return true;
}

bool Player::rotateAboveBoard(const Block& temp) {
	
	if ((block.pos.getX() > board.pos.getX()) &&
		(block.pos.getX() + block.figure.size() < board.pos.getX() + board.board.size() - 1)) {
		block.cleanPrint();
		block = temp;
		block.drawBlock();
		return true;
	}
	return moveDown();
}

void Player::changeColorsMode() {
	
	if (Player::colorsMode)
		Player::colorsMode = false;
	else
		Player::colorsMode = true;
}

// Check if game speed needs to be increased
const bool& Player::checkSpeed(const int& accNum) const {

	if (board.blocks.size() > accNum * BLOCKS_FOR_ACCELERATION || score > accNum * SCORE_FOR_ACCELERATION)
		return true;
	return false;
}

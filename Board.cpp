#include "Board.h"

#include "Player.h"

Board::Board(const Point& _pos, uint _len, uint _width) : pos(_pos), length(_len), width(_width) {
	allocateSize();
	initialEmptyCells();
}

void Board::drawBoard() const {
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {

			if(board[i][j])
			{
			     gotoxy(pos.getX() + i, pos.getY() + j);
			     cout << board[i][j];
			}
		}
	}
}

Board& Board::operator=(const Board& _board)
{
	pos = _board.pos;
	width = _board.width;
	length = _board.length;
	resizeBoundaries(width, length);
	for (size_t i = 0; i < width; ++i)
	     for (size_t j = 0; j < length; ++j)
			board[i][j] = _board.board[i][j];

	blocks.clear();
	for (Block block : blocks)
		blocks.push_back(block);
	return *this;
}


void Board::drawFillCells() const {

	for (int i = 1; i < width-1; i++) {
		for (int j = 1; j < length-1; j++) {

			if (board[i][j] != EMPTY_CELL)
			{
				gotoxy(pos.getX() + i, pos.getY() + j);
				cout << board[i][j];
			}
		}
	}
}

void Board::drawBlocksInBoard()const {

	if (blocks.empty())
		return;
	for (const Block& block : blocks)
		cout << block;
}

// drowing only the boundaries of the boards
void Board::drawBoundaries() {
	
	for (size_t i = 0; i < width; i++) {
		for (size_t j = 0; j < length; j++) {
			if (!i || i == width - 1 || j == length - 1) {
				gotoxy(static_cast<int>(pos.getX() + i) , static_cast<int>(pos.getY() + j));
				cout << board[i][j];
			}
		}
	}
}

void Board::cleanBoard() {
	
	for (int i = 1; i < width - 1; i++)
		for (int j = 1; j < length - 1; j++)
			board[i][j] = EMPTY_CELL;
	blocks.clear();
}

// Alocating the board rows and columns size 
void Board::allocateSize() {
	
	board.resize(width);
	for (int i = 0; i < width; i++)
		board[i].resize(length);
}

// initializing all the cells to EMPTY_CELL character
void Board::initialEmptyCells() {
	
	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++)
			board[i][j] = EMPTY_CELL;
}

// Sets the characters of the board boundaries
void Board::setBottomBoundary() {
	
	for (int i = 0; i < width; i++)
		board[i][length - 1] = FLOOR;
}

void Board::setTopBoundary() {
	
	for (int i = 0; i < width; i++)
		board[i][0] = FLOOR;
}

void Board::setLeftBoundary() {
	
	for (int i = 0; i < length; i++)
		board[0][i] = WALL;
}

void Board::setRightBoundary() {
	
	for (int i = 0; i < length; i++)
		board[width - 1][i] = WALL;
}

// Sets all board boundaries including corners
void Board::setAllBoundaries() {
	
	setTopBoundary();
	setRightBoundary();
	setLeftBoundary();
	setBottomBoundary();
	board[0][0] = UP_LEFT;
	board[width - 1][0] = UP_RIGHT;
	board[0][length - 1] = DOWN_LEFT;
	board[width - 1][length - 1] = DOWN_RIGHT;
}

// Gets a row and sets FLOOR characters in the board 
void Board::setSeparators(uint const& row) {
	
	for (int i = 0; i < width; i++) {
		if (i && i < width - 1)
			board[i][row] = FLOOR;
		else if (i)
			board[i][row] = RIGHT_CONNECTOR;
		else
			board[i][row] = LEFT_CONNECTOR;
	}
}

// Inserting a block that ended a movement
void Board::freezeBlock(Block& block) {

	for (int i = 0; i < block.figure.size(); i++) {
		for (int j = 0; j < block.figure[i].size(); j++) {
			if (block.figure[i][j])
				board[block.pos.getX() + i - pos.getX()][block.pos.getY() + j - pos.getY()] = Block::SHAPE_AFTER_FREEZE;
		}
	}
	block.shape = Block::SHAPE_AFTER_FREEZE;
	blocks.push_back(block);
}

void Board::freezeWithoutSave(Block& block)
{
	for (int i = 0; i < block.figure.size(); i++) {
		for (int j = 0; j < block.figure[i].size(); j++) {
			if (block.figure[i][j])
				board[block.pos.getX() + i - pos.getX()][block.pos.getY() + j - pos.getY()] = Block::SHAPE_AFTER_FREEZE;
		}
	}
}


void Board::deleteBlock(const Block& block)
{
	for (int i = 0; i < block.figure.size(); i++) {
		for (int j = 0; j < block.figure[i].size(); j++) {
			if (block.figure[i][j])
				board[block.pos.getX() + i - pos.getX()][block.pos.getY() + j - pos.getY()] = EMPTY_CELL;
		}
	}
}


void Board::explosion(const Block& block)
{
	int x = block.pos.getX() - pos.getX(), y = block.pos.getY() - pos.getY();
	size_t startX = (x - Bomb::EXPLOSION_RANGE > 0) ? x - Bomb::EXPLOSION_RANGE : 1;
	size_t startY = (y - Bomb::EXPLOSION_RANGE > 0) ? y - Bomb::EXPLOSION_RANGE : 1;
	size_t endX = (x + Bomb::EXPLOSION_RANGE < width - 1) ? x + Bomb::EXPLOSION_RANGE : width - 2;
	size_t endY = (y + Bomb::EXPLOSION_RANGE < length - 1) ? y + Bomb::EXPLOSION_RANGE : length - 2;
	size_t counter = 0;

	for (size_t i = startX; i <= endX; ++i)
	{
		for (size_t j = startY; j <= endY; ++j)
		{
			if (board[i][j] != EMPTY_CELL)
			{
			     counter++;
			     board[i][j] = EMPTY_CELL;
			}
		}
	}
	for (int i = startY; i <= endY; i++)
		dropRows(startX, endX, i, endY);
	blocks.clear();
	cout << *this;
}

int Board::explosionCheck(const Block& block)
{
	int x = block.pos.getX() - pos.getX(), y = block.pos.getY() - pos.getY();
	size_t startX = (x - Bomb::EXPLOSION_RANGE > 0) ? x - Bomb::EXPLOSION_RANGE : 1;
	size_t startY = (y - Bomb::EXPLOSION_RANGE > 0) ? y - Bomb::EXPLOSION_RANGE : 1;
	size_t endX = (x + Bomb::EXPLOSION_RANGE < width - 1) ? x + Bomb::EXPLOSION_RANGE : width - 2;
	size_t endY = (y + Bomb::EXPLOSION_RANGE < length - 1) ? y + Bomb::EXPLOSION_RANGE : length - 2;
	int counter = 0;

	for (size_t i = startX; i <= endX; ++i)
		for (size_t j = startY; j <= endY; ++j)
			if (board[i][j] != EMPTY_CELL)
				counter++;
	return counter;
}

void Board::resizeBoundaries(const int& x, const int& y) {
	
	int tempW = width, tempL = length;
	width = x;
	length = y;
	allocateSize();
	if (width > tempW)
		for (int i = tempW; i < width; i++)
			for (int j = 0; j < length; j++)
				board[i][j] = EMPTY_CELL;
	if (length > tempL)
		for (int i = 0; i < width; i++)
			for (int j = tempL; j < length; j++)
				board[i][j] = EMPTY_CELL;
}

// Checks if there are full lines that need to be deleted 
uint Board::checkBoard() {
	
	ushort count = 0;
	for (size_t i = 1; i < length - 1; i++) {
		if (isFullRow(i, 1, width - 2)) {
			dropRows(1, width - 2, i, i + 1);
			drawBlocksInBoard();
			drawBoundaries();
			count++;
			return count + checkBoard();
		}
	}
	return count;
}

// Checks if there are full lines that need to be deleted 
uint Board::checkBoardWithoutChanges() {

	ushort count = 0;
	for (size_t i = 1; i < length - 1; i++) {
		if (isFullRow(i, 1, width - 2)) {
			dropRows(1, width - 2, i, i + 1);
			drawBoundaries();
			count++;
			return count + checkBoardWithoutChanges();
		}
	}
	return count;
}

bool Board::isFullRow(const uint& row, const uint& start, const uint& end) {

	for (int i = start; i <= end; i++)
		if (board[i][row] == EMPTY_CELL)
			return false;
	return true;
}

void Board::dropRows(const uint& startX, const uint& endX, const uint& startY, const uint& endY) {

	dropBlocks(startY);
	for (int i = startX; i <= endX; i++)
	{
		for (int j = startY; j >= 1; j--) 
		{
			board[i][j] = board[i][j - 1];
			gotoxy(pos.getX() + i, pos.getY() + j);
			cout << board[i][j];
		}
	}
}
void Board::dropBlocks(const uint& row) {

	int temp = 0;
	for (int i = 0; i < blocks.size(); ++i) {
		if (temp = isFigureInRow(blocks[i], row) >= 0)
			blocks[i].DropRows(temp);
		else if (temp == -1)
		{
			blocks[i].cleanPrint();
			if (!blocks[i].isCleanMatrix())
				DropBlock(blocks[i]);
		}
	}
}


// Loop of moving the block down until it comes across another block or the board border
void Board::DropBlock(Block& block) {

	while (moveDown(&block))
		block.pos++;
}

int Board::isFigureInRow(Block& block, const uint& row) const {
	
	if (block.pos.getY() + block.figure[0].size() < pos.getY() + row)
		return -1;
	for (int i = 0; i < block.figure[0].size(); ++i) {
		if ((block.pos.getY() + i == pos.getY() + row))
			return i;
	}
	return -2;
}

void Board::fillAllBoard(const uchar& shape) {
	
	for (size_t i = 0; i < board.size(); ++i)
		for (size_t j = 0; j < board[i].size(); ++j)
			board[i][j] = shape;
}

/* A function that checks if a down step is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Board::moveDown(Block* block) {

	if (block->pos.getY() < pos.getY()) {
		//block->moveDown();
		return true;
	}
	for (int i = 0; i < block->figure.size(); i++) {
		for (int j = 0; j < block->figure[i].size(); j++) {
			if (block->figure[i][j] &&
				(board[block->pos.getX() + i - pos.getX()][block->pos.getY() + j + 1 - pos.getY()] != ' '))
				return false;
		}
	}
	//block->moveDown();
	return true;
}

/* A function that checks if a left step is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Board::moveLeft(Block* block) {

	if (block->pos.getY() < pos.getY())
		return moveLeftAboveBoard(block);
	for (int i = 0; i < block->figure.size(); i++) {
		for (int j = 0; j < block->figure[i].size(); j++) {
			if (block->figure[i][j] &&
				(board[block->pos.getX() + i -1 - pos.getX()][block->pos.getY() + j - pos.getY()]!= EMPTY_CELL)) {
				return false;
			}
		}
	}
	//block->moveLeft();
	return true;
}

bool Board::moveLeftAboveBoard(Block* block) {

	if (block->pos.getX() > pos.getX() + 1) {
		//block->moveLeft();
		return true;
	}
	//direction = DEFAULT;
	return false;
}

/* A function that checks if a right step is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Board::moveRight(Block* block) {

	if (block->pos.getY() < pos.getY())
		return moveRightAboveBoard(block);
	for (int i = 0; i < block->figure.size(); i++) {
		for (int j = 0; j < block->figure[i].size(); j++) {
			if (block->figure[i][j] &&
				(board[block->pos.getX() + i + 1 - pos.getX()][block->pos.getY() + j - pos.getY()]!= EMPTY_CELL)) {
				//direction = DEFAULT;
				return false;
			}
		}
	}
	//block->moveRight();
	return true;
}

bool Board::moveRightAboveBoard(Block* block) {

	if (block->pos.getX() + block->figure.size() < pos.getX() + board.size() - 1) {
		block->moveRight();
		return true;
	}
	//direction = DEFAULT;
	return false;
}

/* A function that checks if a clockwise rotate is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Board::clockwiseRotate(Block* block) {

	Block temp = *block;
	temp.clockwiseRotate();
	if (block->pos.getY() < pos.getY())
		return rotateAboveBoard(block, temp);
	for (int i = 0; i < block->figure.size(); i++) {
		for (int j = 0; j < block->figure[i].size(); j++) {
			if (temp.figure[i][j] &&
				(board[temp.pos.getX() + i - pos.getX()][temp.pos.getY() + j - pos.getY()] != EMPTY_CELL))
				return false;

		}
	}
	//block->cleanPrint();
	//*block = temp;
	//block->drawBlock();
	return true;
}

/* A function that checks if a counter clockwise rotate is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Board::counterClockwiseRotate(Block* block) {

	Block temp = *block;
	temp.counterClockwiseRotate();
	if (block->pos.getY() < pos.getY())
		return rotateAboveBoard(block, temp);
	for (int i = 0; i < block->figure.size(); i++) {
		for (int j = 0; j < block->figure[i].size(); j++) {
			if (temp.figure[i][j] &&
				(board[temp.pos.getX() + i - pos.getX()][temp.pos.getY() + j - pos.getY()] != EMPTY_CELL))
				return false;

		}
	}
	//block->cleanPrint();
	//*block = temp;
	//block->drawBlock();
	return true;
}

bool Board::rotateAboveBoard(Block* block, const Block& temp) {

	if ((block->pos.getX() > pos.getX()) &&
		(block->pos.getX() + block->figure.size() < pos.getX() + board.size() - 1)) {
		//block->cleanPrint();
		//*block = temp;
		//block->drawBlock();
		return true;
	}
	return false;
}

Point Board::findBestPos(Block* block, short& situations)
{
	Board* b = new Board;
	*b = *this;
	Block temp = *block;
	temp.pos = pos;
	if (typeid(*block) == typeid(Bomb))
		return findBestBombPos(b,temp);
	int bestSituation = situations;
	uint maxFullRows = 0, fullRows = 0;
	Point bestPos;
	Point lowestPos = bestPos = block->pos;

	for (size_t i = 0; i < situations; ++i)
	{
		for (size_t j = 1; j < width - 3 && b->moveRight(&temp); ++j)
		{
			temp.pos >>= j;
			temp.cleanPrint();
			b->DropBlock(temp);
			b->freezeBlock(temp);
			fullRows = b->checkBoardWithoutChanges();
			if (fullRows > maxFullRows)
			{
				maxFullRows = fullRows;
				bestPos = temp.pos;
				bestSituation = i;
			}
			if (!maxFullRows && lowestPos.compareY(temp.pos) > 0)
			{
				lowestPos = temp.pos;
				bestSituation = i;
			}
			b->deleteBlock(temp);
			temp.pos = pos;

		}
		temp.pos = pos;
		temp.clockwiseRotate();
	}
	temp.cleanPrint();
	situations = bestSituation;
	delete b;
	return (maxFullRows) ? bestPos : lowestPos;
}

Point Board::findBestBombPos(Board* b, Block& temp)const
{
	Point bestPos = temp.pos;
	int counter;
	int max = counter = -1;

	for (size_t j = 1; j < width - 1 && b->moveRight(&temp); ++j)
	{
		temp.pos >>= j;
		b->DropBlock(temp);
		counter = b->explosionCheck(temp);
		if (counter > max)
		{
			max = counter;
			bestPos = temp.pos;
		}
		else if (counter == max && bestPos.compareY(temp.pos) < 0)
			bestPos = temp.pos;
		b->deleteBlock(temp);
		temp.pos = pos;
	}
	delete b;
	return bestPos;
}





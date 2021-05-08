#include "Board.h"

#include "Player.h"

Board::Board(const Point& _pos, uint _len, uint _width) : pos(_pos), length(_len), width(_width) {
	allocateSize();
	initialEmptyCells();
}

Point Board::getPointByPosition(const Point& pos)const
{
	for (size_t i = 0; i < width; ++i)
		for (size_t j = 0; j < length; ++j)
			if (board[i][j] == pos)
				return board[i][j];
	return { -1,-1 };
}


void Board::setBoardPos(const Point& newPos)
{
	pos = newPos;
	for (size_t i = 0; i < width; ++i)
		for (size_t j = 0; j < length; ++j)
			board[i][j].setXY(pos.x + i, pos.y + j);
}


void Board::drawBoard() const {

	for (int i = 0; i < width; i++) 
		for (int j = 0; j < length; j++) 
			cout << board[i][j];
}

void Board::drawBoard(const Color& color) const
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++)
			board[i][j].draw(color);
}


Board& Board::operator=(const Board& _board)
{
	if (this != &_board)
	{
		pos = _board.pos;
		width = _board.width;
		length = _board.length;
		resizeBoundaries(width, length);
		for (size_t i = 0; i < width; ++i)
			for (size_t j = 0; j < length; ++j)
				board[i][j] = _board.board[i][j];
	}
	return *this;
}


void Board::drawFillCells() const {

	for (int i = 0; i < width; i++) 
		for (int j = 0; j < length; j++) 
			if (board[i][j].shape != EMPTY_CELL)
				cout << board[i][j];
}

void Board::drawEmptyCells() const
{
	for (int i = 1; i < width - 1; i++) 
		for (int j = 1; j < length - 1; j++) 
			if (board[i][j].shape == EMPTY_CELL)
				cout << board[i][j];	
}

// drowing only the boundaries of the boards
void Board::drawBoundaries()const {

	for (size_t i = 0; i < width; i++) 
		for (size_t j = 0; j < length; j++) 
			if (!i || i == width - 1 || j == length - 1) 
				cout << board[i][j];
}

void Board::cleanBoard() {

	for (int i = 1; i < width-1; i++) 
		for (int j = 1; j < length-1; j++) 
			board[i][j].shape = EMPTY_CELL;
	drawEmptyCells();
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
	{
	     for (int j = 0; j < length; j++)
	     {
			board[i][j].x = pos.x + i;
			board[i][j].y = pos.y + j;
			board[i][j].shape = EMPTY_CELL;
	     }   
	}
}

// Sets the characters of the board boundaries
void Board::setBottomBoundary() {

	for (int i = 0; i < width; i++)
		board[i][length - 1].shape = FLOOR;
}

void Board::setTopBoundary() {

	for (int i = 0; i < width; i++)
		board[i][0].shape = FLOOR;
}

void Board::setLeftBoundary() {

	for (int i = 0; i < length; i++)
		board[0][i].shape = WALL;
}

void Board::setRightBoundary() {

	for (int i = 0; i < length; i++)
		board[width - 1][i].shape = WALL;
}

// Sets all board boundaries including corners
void Board::setAllBoundaries() {

	setTopBoundary();
	setRightBoundary();
	setLeftBoundary();
	setBottomBoundary();
	board[0][0].shape = UP_LEFT;
	board[width - 1][0].shape = UP_RIGHT;
	board[0][length - 1].shape = DOWN_LEFT;
	board[width - 1][length - 1].shape = DOWN_RIGHT;
}

// Gets a row and sets FLOOR characters in the board 
void Board::setSeparators(uint const& row) {

	for (int i = 0; i < width; i++) {
		if (i && i < width - 1)
			board[i][row].shape = FLOOR;
		else if (i)
			board[i][row].shape = RIGHT_CONNECTOR;
		else
			board[i][row].shape = LEFT_CONNECTOR;
	}
}

// Inserting a block that ended a movement
void Board::freezeBlock(const Block& block)
{

	for (int i = 0; i < block.figure.size(); i++) {
		for (int j = 0; j < block.figure[i].size(); j++) {
			if (block.figure[i][j])
			{
				int x, y;
				board[x = block.pos.getX() + i - pos.getX()][y = block.pos.getY() + j - pos.getY()].shape = Block::SHAPE_AFTER_FREEZE;
				board[x][y].color = block.color;
			}
		}
	}
}


void Board::deleteBlock(const Block& block)
{
	for (int i = 0; i < block.figure.size(); i++) {
		for (int j = 0; j < block.figure[i].size(); j++) {
			if (block.figure[i][j])
				board[block.pos.getX() + i - pos.getX()][block.pos.getY() + j - pos.getY()].shape = EMPTY_CELL;
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
		for (size_t j = startY; j <= endY; ++j)
			board[i][j].shape = EMPTY_CELL;
	fixBoard(1, width - 2, endY, startY);
}

void Board::fixBoard(const size_t& startX, const size_t& endX, const size_t& startY, const size_t& endY)
{
	for (size_t i = startY; i >= endY; --i)
	{
		for (size_t j = startX; j <= endX; ++j)
		{
			if (board[j][i].shape != EMPTY_CELL && board[j][i + 1].shape == EMPTY_CELL && (!isWellConnected(j, i)))
			{
				size_t n = i + 1;
				while (board[j][n++].shape == EMPTY_CELL && n < length - 1) {}
				board[j][n - 1].shape = board[j][i].shape;
				board[j][i].shape = EMPTY_CELL;
			}
		}
	}
	drawEmptyCells();
}

bool Board::isWellConnected(const size_t& x, const size_t& y)
{
	const size_t right = x + 1, left = x - 1, down = y + 1;
	if (down >= length - 1)
		return false;
	if (board[x][down].shape != EMPTY_CELL)
		return true;
	if (right < width - 1)
	{
		if (board[right][y].shape != EMPTY_CELL && board[right][down].shape != EMPTY_CELL)
			return true;
	}
	if (left)
	{
		if (board[left][y].shape != EMPTY_CELL && board[left][down].shape != EMPTY_CELL)
			return true;
	}
	return false;
}


size_t Board::explosionCheck(const Block& block)const
{
	int x = block.pos.getX() - pos.getX(), y = block.pos.getY() - pos.getY();
	size_t startX = (x - Bomb::EXPLOSION_RANGE > 0) ? x - Bomb::EXPLOSION_RANGE : 1;
	size_t startY = (y - Bomb::EXPLOSION_RANGE > 0) ? y - Bomb::EXPLOSION_RANGE : 1;
	size_t endX = (x + Bomb::EXPLOSION_RANGE < width - 1) ? x + Bomb::EXPLOSION_RANGE : width - 2;
	size_t endY = (y + Bomb::EXPLOSION_RANGE < length - 1) ? y + Bomb::EXPLOSION_RANGE : length - 2;
	size_t counter = 0;

	for (size_t i = startX; i <= endX; ++i)
		for (size_t j = startY; j <= endY; ++j)
			if (board[i][j].shape != EMPTY_CELL)
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
				board[i][j].shape = EMPTY_CELL;
	if (length > tempL)
		for (int i = 0; i < width; i++)
			for (int j = tempL; j < length; j++)
				board[i][j].shape = EMPTY_CELL;
}

// Checks if there are full lines that need to be deleted 
uint Board::checkBoard() {

	ushort count = 0;
	for (size_t i = 1; i < length - 1; i++) {
		if (isFullRow(i, 1, width - 2)) {
			for (size_t j = 1; j < width - 1; ++j)
				board[j][i].shape = EMPTY_CELL;
			fixBoard(1, width - 2, i, 1);
			count++;
			return count + checkBoard();
		}
	}
	return count;
}


bool Board::isFullRow(const size_t& row, const size_t& start, const size_t& end)const {

	for (size_t i = start; i <= end; ++i)
		if (board[i][row].shape == EMPTY_CELL)
			return false;
	return true;
}

bool Board::isEmptyRow(const size_t& row, const size_t& start, const size_t& end)const {

	for (size_t i = start; i <= end; ++i)
		if (board[i][row].shape != EMPTY_CELL)
			return false;
	return true;
}

void Board::dropRows(const size_t& startX, const size_t& endX, const size_t& startY) {

	//dropBlocks(startY);
	for (size_t i = startX; i <= endX; i++)
	{
		for (size_t j = startY; j >= 1; j--)
		{
			board[i][j] = board[i][j - 1];
			gotoxy(pos.getX() + i, pos.getY() + j);
			cout << board[i][j];
		}
	}
}


// Loop of moving the block down until it comes across another block or the board border
void Board::DropBlock(Block& block) {

	while (moveDown(&block))
		block.pos++;
}

int Board::isFigureInRow(Block& block, const size_t& row) const {

	if (block.pos.getY() + block.figure[0].size() < row + pos.getY())
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
			board[i][j].shape = shape;
}

/* A function that checks if a down step is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Board::moveDown(const Block* block)const {

	if (block->pos.getY() < pos.getY())
		return true;
	for (int i = 0; i < block->figure.size(); i++) {
		for (int j = 0; j < block->figure[i].size(); j++) {
			if (block->figure[i][j] &&
				(board[block->pos.getX() + i - pos.getX()][block->pos.getY() + j + 1 - pos.getY()].shape != ' '))
				return false;
		}
	}
	return true;
}

/* A function that checks if a left step is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Board::moveLeft(const Block* block)const {

	if (block->pos.getY() < pos.getY())
		return moveLeftAboveBoard(block);
	for (int i = 0; i < block->figure.size(); i++) {
		for (int j = 0; j < block->figure[i].size(); j++) {
			if (block->figure[i][j] &&
				(board[block->pos.getX() + i - 1 - pos.getX()][block->pos.getY() + j - pos.getY()].shape != EMPTY_CELL)) {
				return false;
			}
		}
	}
	return true;
}

bool Board::moveLeftAboveBoard(const Block* block)const {

	if (block->pos.getX() > pos.getX() + 1)
		return true;
	return false;
}

/* A function that checks if a right step is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Board::moveRight(const Block* block)const {

	if (block->pos.getY() < pos.getY())
		return moveRightAboveBoard(block);
	for (int i = 0; i < block->figure.size(); i++) {
		for (int j = 0; j < block->figure[i].size(); j++) {
			if (block->figure[i][j] &&
				(board[i + block->pos.getX() + 1 - pos.getX()][j + block->pos.getY() - pos.getY()].shape != EMPTY_CELL)) {
				return false;
			}
		}
	}
	return true;
}

bool Board::moveRightAboveBoard(const Block* block)const {

	if (block->pos.getX() + block->figure.size() < pos.getX() + board.size() - 1)
		return true;
	return false;
}

bool Board::rotateCheck(Block* block, const ushort& dir)const
{
	Block temp = *block;
	for (size_t i = 0; i < temp.figure.size(); ++i)
	{
		if (dir == CLOCKWISE && !clockwiseRotate(&temp) || dir == COUNTER_CLOCKWISE && !counterClockwiseRotate(&temp))
		{
			if (temp.pos.getX() > (pos.getX() + width) / 2)
				temp.pos <<= 1;
			else
				temp.pos >>= 1;
		}
		else
		{
			block->pos = temp.pos;
			return true;
		}
	}
	return false;
}


/* A function that checks if a clockwise rotate is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Board::clockwiseRotate(const Block* block)const
{

	Block temp = *block;
	temp.clockwiseRotate();
	if (block->pos.getY() < pos.getY())
		return rotateAboveBoard(temp);
	for (int i = 0; i < block->figure.size(); i++) {
		for (int j = 0; j < block->figure[i].size(); j++) {
			if (temp.figure[i][j] &&
				(board[i + temp.pos.getX() - pos.getX()][j + temp.pos.getY() - pos.getY()].shape != EMPTY_CELL))
				return false;

		}
	}
	return true;
}

/* A function that checks if a counter clockwise rotate is valid,
 * valid - tells the block to execute and returns true,
 * not valid -  does not execute and returns no */
bool Board::counterClockwiseRotate(const Block* block)const
{

	Block temp = *block;
	temp.counterClockwiseRotate();
	if (block->pos.getY() < pos.getY())
		return rotateAboveBoard(temp);
	for (int i = 0; i < block->figure.size(); i++) {
		for (int j = 0; j < block->figure[i].size(); j++) {
			if (temp.figure[i][j] &&
				(board[i + temp.pos.getX() - pos.getX()][j + temp.pos.getY() - pos.getY()].shape != EMPTY_CELL))
				return false;
		}
	}
	return true;
}

bool Board::rotateAboveBoard(const Block& temp)const
{
	if ((temp.pos.getX() > pos.getX()) &&
		(temp.pos.getX() + temp.figure.size() < pos.getX() + board.size() - 1))
		return true;
	return false;
}

size_t Board::countEmptyCells(const size_t& row)const
{
	size_t count = 0;
	for (size_t i = 1; i < width - 1; ++i)
		if (board[i][row].shape == EMPTY_CELL)
			++count;
	return count;
}

size_t Board::topRow()const
{
	size_t count = 0, i = 1;

	while (i < length - 1)
	{
		if (!isEmptyRow(i, 1, width - 2))
			return i;
		++i;
	}
	return 0;
}

bool Board::isThereAccess(const size_t& x, const size_t& y)
{
	for (size_t i = y - 1; i > 0; --i)
		if (board[x][i].shape != EMPTY_CELL)
			return false;
	return true;
}


bool Board::notDisturbing(const Block& block)const
{
	size_t row = topRow();
	for (size_t i = 0; i < Block::ROWS && row < length - 1; ++i)
	{
		if (countEmptyCells(row) == 1 && isBlocksAccess(block, row))
			return false;

		row++;
	}
	return true;
}


vector<Point> Board::getEmptyCellsInRow(const size_t& row)const
{
	vector<Point> empty;
	for (size_t i = width - 2; i > 0; --i)
		if (board[i][row].shape == EMPTY_CELL)
			empty.push_back(board[i][row]);
	return empty;
}


bool Board::isBlocksAccess(const Block& block, const size_t& row)const
{
	vector<Point> empty = getEmptyCellsInRow(row);
	for (size_t i = 0; i < Block::COLUMNS; ++i)
	{
	     for (size_t j = 0; j < Block::ROWS; ++j)
	     {
	          if(block.figure[i][j])
	          {
				const Point& temp = getPointByPosition({ block.pos.x + i,block.pos.y + j });
	               for(Point& p:empty)
	               {
					
					if ((!temp.compareX(p)) && temp.compareY(p) > 0)
						return true;
	               }
	          }      
	     }
	}
	return false;
}



Point Board::findBestPos(Block* block, short& situations)
{
	vector<Block> options;
	Board* b = new Board;
	Block* temp = new Block;
	*b = *this;
	*temp = *block;
	temp->pos = pos;
	if (typeid(*block) == typeid(Bomb))
		return findBestBombPos(b,temp);
	short bestSituation = situations;
	uint maxFullRows = 0, fullRows = 0;
	Point bestPos;
	Point lowestPos = bestPos = block->pos;
	options.push_back(*block);
	for (short i = 0; i < situations; ++i)
	{
		size_t limit = setLimit(temp);
		for (short j = 1; j <limit && b->moveRight(temp); ++j)
		{
			temp->pos >>= 1;
			temp->cleanPrint();
			b->DropBlock(*temp);
			b->freezeBlock(*temp);
			fullRows = b->checkBoard();
			b->checkMaxFullRows(options,fullRows, maxFullRows, bestPos, lowestPos, temp, bestSituation, i);
			b->deleteBlock(*temp);
			temp->pos.setY(pos.getY());

		}
		b->deleteBlock(*temp);
		temp->pos = pos;
		temp->clockwiseRotate();
	}
	situations = bestSituation;

	if (!maxFullRows)
		bestPos = preferNotInterfere(b,options);

	b->cleanAndDeleteCalculation(temp);
	return bestPos;
}

Point& Board::preferNotInterfere(Board* b, vector<Block>& options) const
{
	int i = options.size() - 1;
	while (i >= 0)
	{
		if (notDisturbing(options[i]))
			return options[i].pos;
		i--;
	}
	return options[options.size() - 1].pos;
}

size_t Board::setLimit(const Block* block)const
{
	size_t limit = width - 3;
	if (block->isColEmpty(Block::COLUMNS - 1) && block->isColEmpty(Block::COLUMNS - 2) && block->isColEmpty(Block::COLUMNS - 3))
		limit = width - 1;
	else if (block->isColEmpty(Block::COLUMNS - 1) && block->isColEmpty(Block::COLUMNS - 2))
		limit = width - 2;
	return limit;
}


Point Board::findBestBombPos(Board* b, Block* temp)const
{
	Point bestPos = temp->pos;
	int counter;
	int max = counter = -1;

	for (size_t j = 1; j < width - 1 && b->moveRight(temp); ++j)
	{
		temp->pos >>= 1;
		b->DropBlock(*temp);
		counter = b->explosionCheck(*temp);
		if (counter > max)
		{
			max = counter;
			bestPos = temp->pos;
		}
		else if (counter == max && bestPos.compareY(temp->pos) < 0)
			bestPos = temp->pos;
		b->deleteBlock(*temp);
		temp->pos.setY(pos.getY());
	}
	b->cleanAndDeleteCalculation(temp);
	return bestPos;
}

void Board::cleanAndDeleteCalculation(Block* temp)
{
	temp->cleanPrint();
	cleanBoard();
	delete temp;
	delete this;
}

void Board::checkMaxFullRows(vector<Block>& options, uint& fullRows, uint& maxFullRows, Point& bestPos, Point& lowestPos,
	const Block* temp, short& bestSituation, short& situation)const
{
	if (fullRows > maxFullRows)
	{
		maxFullRows = fullRows;
		bestPos = temp->pos;
		bestSituation = situation;
		options.push_back(*temp);
	}
	if (!maxFullRows && lowestPos.compareY(temp->pos) > 0)
	{
		lowestPos = temp->pos;
		bestSituation = situation;
		options.push_back(*temp);
	}

}


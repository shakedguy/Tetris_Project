#include "Board.h"

#include "Game.h"


Board::Board(const Point& _pos, const size_t& _len, const size_t& _width, const Color& _color) :
	pos(_pos), length(_len), width(_width), color(_color) {
	allocateSize();
	initialEmptyCells();
}

bool Board::colorsMode = false;


std::ostream& operator<<(std::ostream& out, const Board& board)
{
	(Board::colorsMode) ? board.drawBoard(board.color) : board.drawBoard(WHITE);
	return out;
}
void Board::changeColorsMode() {

	if (Board::colorsMode)
		Board::colorsMode = false;
	else
		Board::colorsMode = true;
}

Point Board::getPointByPosition(const Point& pos)const
{
	for (size_t i = 0; i < width; ++i)
		for (size_t j = 0; j < length; ++j)
			if (board[i][j].getPoint() == pos)
				return board[i][j].getPoint();
	return { -1,-1 };
}


void Board::getIndexByPosition(const Point& pos, size_t& x, size_t& y) const
{
	for (size_t i = 0; i < width; ++i)
	     for (size_t j = 0; j < length; ++j)
			if (board[i][j].getPoint() == pos) { x = i; y = j; }
}

size_t Board::numOfFillCells()const
{
	size_t counter = 0;
	for (size_t i = 1; i < width-1; ++i)
		for (size_t j = 1; j < length-1; ++j)
			if (board[i][j].shape != EMPTY_CELL)
				counter++;
	return counter;
}

void Board::setPos(const Point& newPos)
{
	pos = newPos;
	for (size_t i = 0; i < width; ++i)
		for (size_t j = 0; j < length; ++j)
			board[i][j].setXY(pos.x + i, pos.y + j);
}


void Board::drawBoard() const
{
	for (size_t i = 0; i < width; ++i)
		for (size_t j = 0; j < length; ++j)
			(Board::colorsMode) ? board[i][j].draw(color) : board[i][j].draw(WHITE);
}

void Board::drawBoard(const Color& color) const
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++)
			board[i][j].draw(color);
}

void Board::cleanArea(size_t startX, size_t endX, size_t startY, size_t endY)
{
	if (startX > endX || startY > endY)
		return;
	endX = (endX < width) ? endX : width - 1;
	endX = (endY < length) ? endX : length - 1;
	for (size_t i = startX; i <= endX; ++i)
		for (size_t j = startY; j <= endY; ++j)
			board[i][j].setShape(EMPTY_CELL);
}

void Board::clearScreen()
{
	for (size_t i = 0; i < board.size(); ++i)
		for (size_t j = 0; j < board[i].size(); ++j)
			board[i][j].setShape(EMPTY_CELL);
}


void Board::assign(const Board& _board)
{
	pos = _board.pos;
	width = _board.width;
	length = _board.length;
	resizeBoundaries(width, length);
	initialEmptyCells();
	board = _board.board;
}


Board& Board::operator=(const Board& _board)
{
	if (this != &_board)
		this->assign(_board);
	return *this;
}

void Board::drawFillCells() const {

	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++)
			if (board[i][j].shape != EMPTY_CELL)
				(Board::colorsMode) ? board[i][j].draw() : board[i][j].draw(WHITE);		
}

void Board::drawEmptyCells() const
{
	for (int i = 1; i < width - 1; i++) 
		for (int j = 1; j < length - 1; j++) 
			if (board[i][j].shape == EMPTY_CELL)
				cout << board[i][j];	
}

// drowing only the boundaries of the boards
void Board::drawBoundaries()const
{

	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			if ((isBoundary(i, j) && board[i][j].shape != EMPTY_CELL)
				|| board[i][j].shape == FLOOR)
				cout << board[i][j];
		}
	}
}

// drowing only the boundaries of the boards
void Board::drawBoundaries(const Color& _color)const
{

	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			if (isBoundary(i,j) && board[i][j].shape != EMPTY_CELL)
				board[i][j].draw(_color);
			else if(board[i][j].shape == FLOOR)
				board[i][j].draw(_color);
		}
	}
}

inline bool Board::isBoundary(const size_t& x, const size_t& y) const
{
	return (!x || x == width - 1 || !y || y == length - 1);
}


void Board::cleanBoard() {

	for (int i = 1; i < width-1; i++) 
		for (int j = 1; j < length-1; j++) 
			board[i][j].shape = EMPTY_CELL;
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
				const int x = block.pos.getX() + i - pos.getX();
				const int y = block.pos.getY() + j - pos.getY();
				board[x][y].color = block.color;
				board[x][y].shape = Block::SHAPE_AFTER_FREEZE;
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
	dropFloatingBricks(1, width-1, endY, 1, endY - startY);
}

size_t Board::damageCounter(const Block& block)const
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

void Board::dropFloatingBricks(const size_t& startX, const size_t& endX, const size_t& startY, const size_t& endY, const size_t& height)
{
	for (size_t i = startY; i >= endY; --i)
	{
		for (size_t j = startX; j <= endX; ++j)
		{
			if (board[j][i].shape != EMPTY_CELL && board[j][i + 1].shape == EMPTY_CELL &&
				(!isWellConnected(j, i)))
			{
				size_t n = i + 1, counter = 0;

				while (board[j][n].shape == EMPTY_CELL &&
					n++ < length - 1 &&
					counter++ < height) {}

				board[j][n - 1].shape = board[j][i].shape;
				board[j][i].shape = EMPTY_CELL;
			}
		}
	}
}

bool Board::isWellConnected(const size_t& x, const size_t& y)
{
	const size_t right = x + 1, left = x - 1, down = y + 1;
	if (down >= length - 1)
		return true;
	if (board[x][down].shape != EMPTY_CELL)
		return true;
	if (right < width - 1)
		if (board[right][y].shape != EMPTY_CELL && board[right][down].shape != EMPTY_CELL)
			return true;
	if (left)
		if (board[left][y].shape != EMPTY_CELL && board[left][down].shape != EMPTY_CELL)
			return true;
	return false;
}

void Board::resizeBoundaries(const size_t& x, const size_t& y) {

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
uint Board::checkBoard(bool draw) {

	ushort count = 0;
	for (size_t i = 1; i < length - 1; i++) {
		if (isFullRow(i, 1, width - 2)) {
			for (size_t j = 1; j < width - 1; ++j)
				board[j][i].shape = EMPTY_CELL;
			dropFloatingBricks(1, width - 2, i, 1,1);
			if (draw)
				drawEmptyCells();
			count++;
			return count + checkBoard(draw);
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

// Loop of moving the block down until it comes across another block or the board border
void Board::DropBlock(Block& block)const {

	while (moveDown(&block))
		++block.pos;
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
				(board[i + block->pos.getX() - pos.getX()][block->pos.getY() + j + 1 - pos.getY()].shape != ' '))
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

size_t Board::getTopRow()const
{
	size_t i = 1;

	while (i < length - 1)
	{
		if (!isEmptyRow(i, 1, width - 2))
			return i;
		++i;
	}
	return 0;
}

bool Board::notDisturbing(const Block& block)const
{
	size_t row = getTopRow();
	for (size_t i = 0; i < Block::ROWS - 2 && row < length - 1; ++i)
	{
		if (countEmptyCells(row) > 0 && countEmptyCells(row) <= 2 && isBlocksAccess(block, row))
			return false;
		++row;
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
				const Point& temp =
					getPointByPosition(Point{ block.pos.x + i,block.pos.y + j });
				for (Point& p : empty)
					if ((!temp.compareX(p)) && temp.compareY(p) > 0)
						return true;
	          }      
	     }
	}
	return false;
}

size_t Board::oneToGoRowsCounter() const
{
	size_t counter = 0, start, top = getTopRow();
	start = (top - 2 >= 1) ? top - 2 : 1;
	top = (top + 2 < length - 1) ? top + 2 : length - 2;
	
	for (size_t i = start; i <= top; ++i)
		if (countEmptyCells(i) == 1)
			++counter;
	return counter;
}

Point Board::getHighestPoint() const
{
	const size_t& topRow = getTopRow();
	for (size_t i = 1; i < board.size() - 1; ++i)
		if (board[i][topRow].shape != EMPTY_CELL)
			return { board[i][topRow].getX(), board[i][topRow].getY()};
	return { -1,-1 };
}

bool Board::isEmpty()const
{
	for(size_t i=1;i<board.size()-1;++i)
		for (size_t j = 1; j < board[i].size(); ++j)
			if (board[i][j].shape != EMPTY_CELL)
				return false;
	return true;
}


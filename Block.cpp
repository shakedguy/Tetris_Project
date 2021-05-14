#include "Block.h"

Block::Block(const Point& _pos) : pos(_pos), shape(SHAPE) {

	std::random_device rnd;
	const std::uniform_int_distribution<> shapeRange(0, 6);
	const std::uniform_int_distribution<> colorRange(1, 14);
	shapeNum = (shapeRange(rnd));
	color = static_cast<Color>(colorRange(rnd));
	//shapeNum = O;
	cleanBlock();
	setFigure();
}

Bomb::Bomb(const Point& _pos, const uchar& _shape)
{
	pos = _pos;
	shape = _shape;
	cleanBlock();
	figure[0][0] = 1;
}

bool Block::colorsMode = false;

void Block::assign(const Block& _block)
{
	cleanBlock();
	for (int i = 0; i < figure.size(); i++)
		for (int j = 0; j < figure[i].size(); j++)
			figure[i][j] = _block.figure[i][j];

	pos = _block.pos;
	shape = _block.shape;
	color = _block.color;
	shapeNum = _block.shapeNum;
	color = _block.color;
}


Block& Block::operator=(const Block& b) {
	if (&b != this)
		this->assign(b);
	return *this;
}

void Block::createNewBlock() {
	
	cleanBlock();
	std::random_device rnd;
	const std::uniform_int_distribution<> shapeRange(0, 6);
	const std::uniform_int_distribution<> colorRange(1, 14);
	shapeNum = (shapeRange(rnd));
	color = static_cast<Color>(colorRange(rnd));
	//shapeNum = O;
	setFigure();
}


/********** Set figures ***********/
void Block::setFigure() {
	
	switch (shapeNum) {
	case I:
		setShapeI();
		break;
	case L:
		setShapeL();
		break;
	case J:
		setShapeJ();
		break;
	case O:
		setShapeO();
		break;
	case S:
		setShapeS();
		break;
	case T:
		setShapeT();
		break;
	case Z:
		setShapeZ();
		break;

	default:
		break;
	}
}

void Block::setShapeI()
{
	for (array<ushort, COLUMNS>& row : figure)
		++row[0];
}

void Block::setShapeL() {
	
	for (size_t i = 0; i < figure.size() - 1; ++i) 
	{
		for (size_t j = 0; j < figure[i].size() - 2; ++j) 
		{
			if (!(i + j))
				++figure[i][j];
			else if (j)
				++figure[i][j];
		}
	}
}

void Block::setShapeJ() {
	
	for (size_t i = 0; i < figure.size() - 1; ++i)
		for (size_t j = 0; j < figure[i].size() - 2; ++j)
			if ((!j && i > 1) || j)
				++figure[i][j];
}

void Block::setShapeO() {
	
	for (size_t i = 0; i < figure.size() - 2; ++i)
		for (size_t j = 0; j < figure[i].size() - 2; ++j)
			++figure[i][j];
}

void Block::setShapeS() {
	
	for (size_t i = 0; i < figure.size() - 1; ++i)
		for (size_t j = 0; j < figure[i].size() - 2; ++j)
			if ((!j && i) || (j && i < 2))
				++figure[i][j];
}


void Block::setShapeT() {
	
	for (size_t i = 0; i < figure.size() - 1; ++i)
		for (size_t j = 0; j < figure[i].size() - 2; ++j)
			if ((!j && i == 1) || j)
				++figure[i][j];
}

void Block::setShapeZ() {
	
	for (size_t i = 0; i < figure.size() - 1; ++i)
		for (size_t j = 0; j < figure[i].size() - 2; ++j)
			if ((!j && i < 2) || (j && i))
				++figure[i][j];
}

/********** End set figures ***********/

/* Swap rows and columns as needed so that the block shape starts at point (0,0) of the matrix */
void Block::arrangeMatrix() {
	
	if (isRowZeroEmpty()) {
		pullFigureUp();
		arrangeMatrix();
	}
	if (isColumnZeroEmpty()) {
		pullFigureLeft();
		arrangeMatrix();
	}
}

// This function checks if the first row is empty
bool Block::isRowZeroEmpty()
{
	for (array<ushort, COLUMNS>& row : figure)
		if (row[0])
			return false;
	return true;
}

//This function checks if the first collumn is empty
bool Block::isColumnZeroEmpty()
{
	for (size_t i = 0; i < ROWS; ++i)
		if (figure[0][i])
			return false;
	return true;
}

/* Swap rows so that the block shape starts with row 0 of the matrix */
void Block::pullFigureUp()
{
	for (size_t i = 0; i < figure.size(); i++)
		for (size_t j = 0; j < figure[i].size() - 1; j++)
			std::swap(figure[i][j], figure[i][j + 1]);
}

/* Swap columns so that the block shape starts with column 0 of the matrix */
void Block::pullFigureLeft() {
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size(); j++)
			std::swap(figure[i][j], figure[i + 1][j]);
}

// This function cleans the block (by reseting the matrix that holds the block's figure)
void Block::cleanBlock() {

	for (int i = 0; i < Block::COLUMNS; i++)
		for (int j = 0; j < Block::ROWS; j++)
			figure[i][j] = 0;
}

// print the EMPTY_CELL on the matrix
void Block::cleanPrint() const {
	for (size_t i = 0; i < figure.size(); i++) {
		for (size_t j = 0; j < figure[i].size(); j++) {
			gotoxy(pos.getX() + i, pos.getY() + j);
			cout << EMPTY_CELL;
		}
	}
}

// This function rotates the block clockwise - transpose the matrix and than reverses the order of the columns
void Block::clockwiseRotate() {
	if (shapeNum == O)
		return;
	transpose_Matrix();
	reverseColumns();
	arrangeMatrix();
}

// this function rotates the block counter clockwise - transpose the matrix and than reverses the order of the rows
void Block::counterClockwiseRotate() {
	if (shapeNum == O)
		return;
	transpose_Matrix();
	reverseRows();
	arrangeMatrix();
}

// This fucntion tranpose the matrix (swaps the collumn and the rows)
void Block::transpose_Matrix() {
	for (size_t i = 0; i < figure.size(); i++)
		for (size_t j = i + 1; j < figure[i].size(); j++)
			std::swap(figure[i][j], figure[j][i]);
}

// Function reverse row order in a matrix
void Block::reverseRows() {
	
	for (size_t i = 0; i < figure.size(); i++) {
		size_t start = 0;
		size_t end = figure[i].size() - 1;

		while (start < end) {
			std::swap(figure[i][start], figure[i][end]);
			start++;
			end--;
		}
	}
}

// Function Reverses the order of the columns in the matrix
void Block::reverseColumns() {
	for (size_t i = 0; i < figure.size(); i++) {
		size_t start = 0;
		size_t end = figure[i].size() - 1;


		while (start < end) {
			std::swap(figure[start][i], figure[end][i]);
			start++;
			end--;
		}
	}
}

void Block::drawBlock() const {
	if (Block::colorsMode)
		setTextColor(color);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {

			if (figure[i][j]) {

				gotoxy(pos.getX() + i, pos.getY() + j);
				//cout << figure[i][j];
				cout << shape;
			}
			else
				gotoxy(0, 0);
		}
	}
	if (Block::colorsMode)
		setTextColor(WHITE);
}

// Raise the y componente in the position data member of the block
void Block::moveDown() {
	cleanPrint();
	pos++;
	cout << *this;
}

// Reduction the x componente in the position data member of the block
void Block::moveLeft() {
	cleanPrint();
	pos <<= 1;
	cout << *this;
}

// Raise the x componente in the position data member of the block
void Block::moveRight() {
	cleanPrint();
	pos >>= 1;
	cout << *this;
}

void Block::changeColorsMode() {
	if (Block::colorsMode)
		Block::colorsMode = false;
	else
		Block::colorsMode = true;
}

bool Block::isCleanMatrix()
{
	for (size_t i = 0; i < figure.size(); ++i)
		for (size_t j = 0; j < figure[i].size(); ++j)
			if (figure[i][j])
				return false;
	return true;
}

bool Block::isColEmpty(const ushort& col)const
{
	for (size_t i = 0; i < Block::ROWS; ++i)
		if (figure[col][i])
			return false;
	return true;
}

size_t Block::getLowestRow()const
{
	size_t max = 0;
	for (size_t i = 0; i < figure.size(); ++i)
		for (size_t j = 0; j < figure[i].size(); ++j)
			if (figure[i][j] && j > max)
				max = j;
	return max;
}







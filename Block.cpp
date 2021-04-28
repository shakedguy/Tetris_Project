#include "Block.h"

Block::Block(Point _pos) : pos(_pos), shape(SHAPE) {
	std::random_device rnd;
	const std::uniform_int_distribution<> shapeRange(0, 6);
	const std::uniform_int_distribution<> colorRange(1, 14);
	shapeNum = (shapeRange(rnd));
	color = static_cast<Color>(colorRange(rnd));
	cleanBlock();
	setFigure();
}

bool Block::colorsMode = false;

Block& Block::operator=(const Block& b) {
	if (&b != this) {
		cleanBlock();
		for (int i = 0; i < figure.size(); i++)
			for (int j = 0; j < figure[i].size(); j++)
				figure[i][j] = b.figure[i][j];

		pos = b.pos;
		shape = b.shape;
		color = b.color;
		shapeNum = b.shapeNum;
		color = b.color;
	}
	return *this;
}

void Block::createNewBlock() {
	
	cleanBlock();
	std::random_device rnd;
	const std::uniform_int_distribution<> shapeRange(0, 6);
	const std::uniform_int_distribution<> colorRange(1, 14);
	shapeNum = (shapeRange(rnd));
	color = static_cast<Color>(colorRange(rnd));
	setFigure();
}


/********** Set figures ***********/
void Block::setFigure() {
	
	switch (shapeNum) {
	case LINE:
		setLineFigure();
		break;
	case L:
		setLfigure();
		break;
	case LEFT_L:
		setLeftLfigure();
		break;
	case DICE:
		setDiceFigure();
		break;
	case RIGHT_STEPS:
		setRightStepsFigure();
		break;
	case CENTER_STEP:
		setCenterStepsFigure();
		break;
	case LEFT_STEPS:
		setLeftStepsFigure();
		break;

	default:
		break;
	}
}

void Block::setLineFigure() {
	
	for (int i = 0; i < figure.size(); i++)
		figure[i][0]++;
}

void Block::setLfigure() {
	
	for (int i = 0; i < figure.size() - 1; i++) {
		for (int j = 0; j < figure[i].size() - 2; j++) {
			if (!(i + j))
				figure[i][j]++;
			else if (j)
				figure[i][j]++;
		}
	}
}

void Block::setLeftLfigure() {
	
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i > 1) || j)
				figure[i][j]++;
}

void Block::setDiceFigure() {
	
	for (int i = 0; i < figure.size() - 2; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			figure[i][j]++;
}

void Block::setRightStepsFigure() {
	
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i) || (j && i < 2))
				figure[i][j]++;
}


void Block::setCenterStepsFigure() {
	
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i == 1) || j)
				figure[i][j]++;
}

void Block::setLeftStepsFigure() {
	
	for (int i = 0; i < figure.size() - 1; i++)
		for (int j = 0; j < figure[i].size() - 2; j++)
			if ((!j && i < 2) || (j && i))
				figure[i][j]++;
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
bool Block::isRowZeroEmpty() {
	for (int i = 0; i < ROWS; i++)
		if (figure[i][0])
			return false;
	return true;
}

//This function checks if the first collumn is empty
bool Block::isColumnZeroEmpty() {
	for (int i = 0; i < figure[0].size(); i++)
		if (figure[0][i])
			return false;
	return true;
}

void Block::DropRows(const uint& row) {
	if (row) {
		for (int i = 0; i < figure.size(); i++)
			for (int j = row; j > 0; j--)
				std::swap(figure[i][j], figure[i][j - 1]);
	}
	for (int i = 0; i < figure.size(); i++)
		figure[i][0] = 0;
}

/* Swap rows so that the block shape starts with row 0 of the matrix */
void Block::pullFigureUp() {
	for (int i = 0; i < figure.size(); i++)
		for (int j = 0; j < figure[i].size() - 1; j++)
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
	//	pos = { 0,0 };
	//shapeNum = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
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
	if (shapeNum == DICE)
		return;
	transpose_Matrix();
	reverseColumns();
	arrangeMatrix();
}

// this function rotates the block counter clockwise - transpose the matrix and than reverses the order of the rows
void Block::counterClockwiseRotate() {
	if (shapeNum == DICE)
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
	for (size_t i = 0; i < figure[i].size(); i++) {
		size_t start = 0;
		size_t end = figure.size() - 1;


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
				cout << shape;
			}
		}
	}
	if (Block::colorsMode)
		setTextColor(WHITE);
}

// Raise the y componente in the position data member of the block
void Block::moveDown() {
	cleanPrint();
	pos++;
	drawBlock();
}

// Reduction the x componente in the position data member of the block
void Block::moveLeft() {
	cleanPrint();
	pos <<= 1;
	drawBlock();
}

// Raise the x componente in the position data member of the block
void Block::moveRight() {
	cleanPrint();
	pos >>= 1;
	drawBlock();
}

void Block::changeColorsMode() {
	if (Block::colorsMode)
		Block::colorsMode = false;
	else
		Block::colorsMode = true;
}

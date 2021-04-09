#include "Player.h"

#include "Game.h"

Player::Player(ushort _playerNum, Point _boardPos, Point _boxPos) : playerNum(_playerNum),
                                                                    boardPos(_boardPos),
                                                                    boxPos(_boxPos),
                                                                    board(boardPos, BOARD_LENGTH, BOARD_WIDTH),
                                                                    box(boxPos)
{
	direction = DEFAULT;
	score = 0;
	if (playerNum == 1)
	{
		block.pos = {LEFT_CURRENT_BLOCK};
		name = "Player 1";
	}
	else
	{
		block.pos = {RIGHT_CURRENT_BLOCK};
		name = "Player 2";
	}
	setGameBoundaries();
	setKeysIndication();
}

bool Player::colorsMode = false;

ostream& operator<<(ostream& out, const Player& _player)
{
	cout << _player.board << _player.box << _player.block;
	_player.drawKeysIndication();
	return out;
}

void Player::setKeysIndication()
{
	for (auto i = 0; i < keyIndicators.size(); i++)
	{
		keyIndicators[i].resizeBoundaries(kEY_INDIVATORS_WIDTH, kEY_INDIVATORS_LENGTH);
		keyIndicators[i].setAllBoundaries();
		if (i < keyIndicators.size() - 2)
			keyIndicators[i].pos = {boardPos.getX() + 4, boardPos.getY() + BOARD_LENGTH + (i * kEY_INDIVATORS_LENGTH) };
	}
	keyIndicators[keyIndicators.size() - 2].pos = {
		keyIndicators[1].pos.getX() - static_cast<int>(keyIndicators[1].width), keyIndicators[1].pos.getY()
	};
	keyIndicators[keyIndicators.size() - 1].pos = {
		static_cast<int>(keyIndicators[1].width) + keyIndicators[1].pos.getX(), keyIndicators[1].pos.getY()
	};
}

void Player::drawKeysIndication()const
{
	for(ushort i=0;i<keyIndicators.size();++i)
	{
		cout << keyIndicators[i];
		gotoxy(keyIndicators[i].pos.getX() + 1, keyIndicators[i].pos.getY() + 1);
		cout << getKey(i);
	}
	//for (const Board& board : keyIndicators)
	//	cout << board;
}

void Player::setName()
{
	gotoxy(WINNING_MASSAGE);
	cout << "Please enter player " << playerNum << " name:  ";
	cin >> name;
	clear_screen();
}

void Player::clearGame()
{
	board.cleanBoard();
	box.clearBox();
	block.createNewBlock();
	setGameBoundaries();
	if (playerNum == 1)
		block.pos = {LEFT_CURRENT_BLOCK};
	else
		block.pos = {RIGHT_CURRENT_BLOCK};
}

void Player::setGameBoundaries()
{
	board.setAllBoundaries();
	for (size_t i = 0; i < board.width; ++i)
		board.board[i][0] = EMPTY_CELL;
}

bool Player::isLost()
{
	for (unsigned int i = 1; i < board.width - 1; ++i)
		if (board.board[i][1] != EMPTY_CELL)
			return true;
	return false;
}

void Player::printScore() const
{
	if (colorsMode)
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
	
	if(colorsMode)
		setTextColor(WHITE);
}

void Player::setPlayerKeys(const string& arrowKeys)
{
	for (sint i = 0; i < arrowKeys.size(); ++i)
	{
		keys.insert({ arrowKeys[i], i });
		if(arrowKeys[i]>='a')
			keys.insert({ arrowKeys[i]-('a'-'A'), i });
		else
			keys.insert({ arrowKeys[i] + ('a' - 'A'), i });
	}
		
}

bool Player::drop()
{
	while (moveDown()) {}
	direction = DEFAULT;
	return false;
}

sint Player::getDirection(const uchar& key)
{
	auto find = keys.find(key);
	if (find != keys.end())
	{
		showIndicateHit(keys.at(find->first));
		return keys.at(find->first);
	}	
	return -1;
}

void Player::showIndicateHit(const ushort& dir)
{

	drawKeysIndication();
	if (colorsMode)
	{
		setTextColor(RED);
		cout << keyIndicators[dir];
		gotoxy(keyIndicators[dir].pos.getX() + 1, keyIndicators[dir].pos.getY() + 1);
		setTextColor(WHITE);
		cout << getKey(dir);
	}
	else
	{
		keyIndicators[dir].fillAllBoard('#');
		cout << keyIndicators[dir];
		gotoxy(keyIndicators[dir].pos.getX() + 1, keyIndicators[dir].pos.getY() + 1);
		cout << getKey(dir);
		keyIndicators[dir].setAllBoundaries();
	}
}
void Player::cleanIndicatorsHit(const ushort& dir)
{
	if (colorsMode)
		setTextColor(WHITE);
	keyIndicators[dir].cleanBoard();
	keyIndicators[dir].setAllBoundaries();
	drawKeysIndication();
}


bool Player::isDown(const uchar& key)
{
	if (keys[key] == DEFAULT)
		return true;
	return false;
}

const uchar& Player::getKey(const ushort& dir)const
{
	for(auto const& pair:keys)
		if (dir == pair.second)
			return pair.first;
	return 0;
}

void Player::getNewBlock()
{
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

void Player::move()
{
	if (!makeTheMove() && direction == DEFAULT)
	{
		board.freezeBlock(block);
		getNewBlock();
		cout << box;
		block.drawBlock();
	}
	board.drawBlocksInBoard();
	board.drawBoundaries();
	score += ((pow(board.checkBoard(), 2)) * POINTS_FOR_FULL_ROW);
}

bool Player::makeTheMove()
{
	switch (direction)
	{
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

bool Player::moveDown()
{
	if (block.pos.getY() < board.pos.getY())
	{
		block.moveDown();
		return true;
	}
	for (int i = 0; i < block.figure.size(); i++)
	{
		for (int j = 0; j < block.figure[i].size(); j++)
		{
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i - boardPos.getX()][block.pos.getY() + j + 1 - boardPos.getY()] != ' ')
			)
				return false;
		}
	}
	block.moveDown();
	return true;
}

bool Player::moveLeft()
{
	if (block.pos.getY() < board.pos.getY())
		return moveLeftAboveBoard();
	for (int i = 0; i < block.figure.size(); i++)
	{
		for (int j = 0; j < block.figure[i].size(); j++)
		{
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i - 1 - boardPos.getX()][block.pos.getY() + j - boardPos.getY()]
					!= EMPTY_CELL))
			{
				direction = DEFAULT;
				return makeTheMove();
			}
		}
	}
	block.moveLeft();
	return true;
}

bool Player::moveLeftAboveBoard()
{
	if (block.pos.getX() > board.pos.getX() + 1)
	{
		block.moveLeft();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove();
}

bool Player::moveRight()
{
	if (block.pos.getY() < board.pos.getY())
		return moveRightAboveBoard();
	for (int i = 0; i < block.figure.size(); i++)
	{
		for (int j = 0; j < block.figure[i].size(); j++)
		{
			if (block.figure[i][j] &&
				(board.board[block.pos.getX() + i + 1 - boardPos.getX()][block.pos.getY() + j - boardPos.getY()]
					!= EMPTY_CELL))
			{
				direction = DEFAULT;
				return makeTheMove();
			}
		}
	}
	block.moveRight();
	return true;
}

bool Player::moveRightAboveBoard()
{
	if (block.pos.getX() + block.figure.size() < board.pos.getX() + board.board.size() - 1)
	{
		block.moveRight();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove();
}

bool Player::clockwiseRotate()
{
	if (block.pos.getY() + block.figure[0].size() >= board.pos.getY() + board.board[0].size())
		return false;
	Block temp = block;
	temp.clockwiseRotate();
	if (block.pos.getY() < board.pos.getY())
		return rotateAboveBoard(temp);
	for (int i = 0; i < block.figure.size(); i++)
	{
		for (int j = 0; j < block.figure[i].size(); j++)
		{
			if (temp.figure[i][j] &&
				(board.board[temp.pos.getX() + i - boardPos.getX()][temp.pos.getY() + j - boardPos.getY()] != EMPTY_CELL
				))
				return false;
		}
	}
	block.cleanPrint();
	block = temp;
	block.drawBlock();
	return true;
}

bool Player::rotateAboveBoard(const Block& temp)
{
	if ((block.pos.getX() > board.pos.getX()) &&
		(block.pos.getX() + block.figure.size() < board.pos.getX() + board.board.size() - 1))

	{
		block.cleanPrint();
		block = temp;
		block.drawBlock();
		return true;
	}
	direction = DEFAULT;
	return makeTheMove();
}

bool Player::counterClockwiseRotate()
{
	if (block.pos.getY() + block.figure[0].size() >= board.pos.getY() + board.board[0].size())
		return false;
	Block temp = block;
	temp.counterClockwiseRotate();
	if (block.pos.getY() < board.pos.getY())
		return rotateAboveBoard(temp);
	for (int i = 0; i < block.figure.size(); i++)
	{
		for (int j = 0; j < block.figure[i].size(); j++)
		{
			if (temp.figure[i][j] &&
				(board.board[temp.pos.getX() + i - boardPos.getX()][temp.pos.getY() + j - boardPos.getY()] != EMPTY_CELL
				))
				return false;
		}
	}
	block.cleanPrint();
	block = temp;
	block.drawBlock();
	return true;
}

void Player::changeColorsMode()
{
	if (colorsMode)
		colorsMode = false;
	else
		colorsMode = true;
}

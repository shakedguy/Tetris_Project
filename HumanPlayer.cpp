#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos, const string& arrowKeys)
{

	Player::playerNum = _playerNum;
	Player::setBoardPos(_boardPos);
	Player::setBoxPos(_boxPos);
	box.setAllBoundaries();

	Player::direction = DEFAULT;
	score = 0;
	if (playerNum == 1) {
		block->pos = { LEFT_BLOCK, BLOCKS_Y };
		name = "Player 1";
	}
	else {
		block->pos = { RIGHT_BLOCK, BLOCKS_Y };
		name = "Player 2";
	}
	setPlayerKeys(arrowKeys);
	Player::setGameBoundaries();
	Player::setKeysIndication();
}

HumanPlayer& HumanPlayer::operator=(const HumanPlayer& _player)
{

	if (this != &_player)
	{
		Player::operator=(_player);
		keys = _player.keys;
	}
	return *this;
}


// Inserting characters and numbers into the step's representation map
void HumanPlayer::setPlayerKeys(const string& arrowKeys) {

	for (sint i = 0; i < arrowKeys.size(); ++i) {

		keys.insert({ arrowKeys[i], i });
		if (arrowKeys[i] >= 'a')
			keys.insert({ arrowKeys[i] - ('a' - 'A'), i });
		else
			keys.insert({ arrowKeys[i] + ('a' - 'A'), i });
	}
}

// Returns the number representing the step, if the character does not belong to the player's step characters, returns -1
sint HumanPlayer::getDirection(const uchar& key) {

	auto find = keys.find(key);
	if (find != keys.end()) {
		Player::showIndicateHit(keys.at(find->first));
		return keys.at(find->first);
	}
	return -1;
}

void HumanPlayer::setDirection(const uchar& key)
{
	short dir = DEFAULT; // initialization the direction to the DEFAULT step
	if ((dir = getDirection(key)) != -1)
		direction = dir;
	else
		direction = DEFAULT;
}

void HumanPlayer::setName() {

	gotoxy(WINNING_MASSAGE);
	cout << "Please enter player " << playerNum << " name:  ";
	cin >> name;
	clrscr();
}

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos,
	const string& arrowKeys) : Player(_playerNum, _boardPos, _boxPos)
{
	setPlayerKeys(arrowKeys);
}

HumanPlayer::HumanPlayer(const HumanPlayer& _player) :
	Player(_player.playerNum, _player.boardPos, _player.boxPos), keys(_player.keys) {}


void HumanPlayer::assign(const HumanPlayer& _player)
{
	Player::operator=(_player);
	keys = _player.keys;
}


HumanPlayer& HumanPlayer::operator=(const HumanPlayer& _player)
{
	if (this != &_player)
		assign(_player);
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

void HumanPlayer::setDirection(const uchar& key, const size_t& cycle)
{
	short dir; // initialization the direction to the DEFAULT step
	if ((dir = getDirection(key)) != -1)
		direction = dir;
	else
		direction = DEFAULT;
}

void HumanPlayer::setName() {

	clrscr();
	gotoxy(Player::NAME_MASSAGE_X, Player::NAME_MASSAGE_Y);
	cout << "Please enter player " << playerNum << " name:  ";
	cin >> name;
	clrscr();
}




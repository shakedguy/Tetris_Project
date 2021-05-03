#include "Computer_Player.h"


ComputerPlayer::ComputerPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos) {

	Player::playerNum = _playerNum;
	Player::setBoardPos(_boardPos);
	Player::setBoxPos(_boxPos);


	Player::direction = DEFAULT;
	score = 0;
	if (playerNum == 1) {
		block->pos = { LEFT_BLOCK, BLOCKS_Y };
		name = "Computer 1";
	}
	else {
		block->pos = { RIGHT_BLOCK, BLOCKS_Y };
		name = "Computer";
	}

	Player::setGameBoundaries();
	Player::setKeysIndication();
}

// Inserting characters and numbers into the step's representation map
void ComputerPlayer::setPlayerKeys(const string& arrowKeys) {

	for (sint i = 0; i < arrowKeys.size(); ++i) {

		keys.insert({ arrowKeys[i], i });
		if (arrowKeys[i] >= 'a')
			keys.insert({ arrowKeys[i] - ('a' - 'A'), i });
		else
			keys.insert({ arrowKeys[i] + ('a' - 'A'), i });
	}
}

// Returns the number representing the step, if the character does not belong to the player's step characters, returns -1
sint ComputerPlayer::getDirection(const uchar& key) {

	auto find = keys.find(key);
	if (find != keys.end()) {
		Player::showIndicateHit(keys.at(find->first));
		return keys.at(find->first);
	}
	return -1;
}

// Gets a key and returns if it represents the DEFAULT direction
bool ComputerPlayer::isDown(const uchar& key) {

	if (keys[key] == DEFAULT)
		return true;
	return false;
}

// Gets a direction and returns the characters representation, if its the DEFAULT direction, returns 0
uchar ComputerPlayer::getKey(const ushort& dir) const {

	for (auto const& pair : keys)
		if (dir == pair.second)
			return pair.first;
	return 0;
}

void ComputerPlayer::setDirection(const uchar& key)
{
	direction = calculateNextMove();
}

ushort ComputerPlayer::calculateNextMove()
{
	return DEFAULT;
}
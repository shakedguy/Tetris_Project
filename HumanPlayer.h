/***************************************
     Header file for class "Human Player" - Player's son.
***************************************/

#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include "Player.h"

class HumanPlayer : public Player
{

     map<uchar, sint> keys;

public:
     HumanPlayer() : HumanPlayer(0, { 0, 0 }, { 0, 0 }) {}
     HumanPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos, const string& arrowKeys = "");
     HumanPlayer(const HumanPlayer& _humanPlayer) { *this = _humanPlayer; }
     HumanPlayer& operator=(const HumanPlayer& _player);
     void setPlayerKeys(const string& arrowKeys)override;
     sint getDirection(const uchar& key)override;
     void setDirection(const uchar& key)override;
     void setName()override;
     void initializeCalculate()override { return; }

};

#endif

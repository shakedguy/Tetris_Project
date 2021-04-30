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
     HumanPlayer() : HumanPlayer(0, { 0, 0 }, { 0, 0 }){}
     HumanPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos);
     ~HumanPlayer() = default;
     void setPlayerKeys(const string& arrowKeys)override;
     sint getDirection(const uchar& key)override;
     bool isDown(const uchar& key)override;
     uchar getKey(const ushort& dir) const override;


};

#endif

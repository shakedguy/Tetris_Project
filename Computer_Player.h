/***************************************
     Header file for class "Computer Player" - Player's son.
***************************************/

#ifndef _COMPUTER_PLAYER_H_
#define _COMPUTER_PLAYER_H_
#include "Player.h"

class ComputerPlayer : public Player
{

     map<uchar, sint> keys;

private:
     ushort calculateNextMove();

public:
     ComputerPlayer() : ComputerPlayer(0, { 0, 0 }, { 0, 0 }) {}
     ComputerPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos);
     ~ComputerPlayer() = default;
     void setPlayerKeys(const string & arrowKeys)override;
     sint getDirection(const uchar & key)override;
     bool isDown(const uchar & key)override;
     uchar getKey(const ushort & dir) const override;
     void setDirection(const uchar& key)override;
     void setName()override { return; }
    

};

#endif
/***************************************
     Header file for class "Human Player" - Player's son.
***************************************/

#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include "FilePlayer.h"
#include "Player.h"

class HumanPlayer : virtual public Player
{

     map<uchar, sint> keys;

private:
    void assign(const HumanPlayer& _player);

public:
     HumanPlayer() : HumanPlayer(0, { 0, 0 }, { 0, 0 }) {}
     HumanPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos,
         const string& arrowKeys = "");
     HumanPlayer(const HumanPlayer& _player);
     HumanPlayer& operator=(const HumanPlayer& _player);
     HumanPlayer& operator*()override { return *this; }
     HumanPlayer* operator->() override { return this; }
     void setPlayerKeys(const string& arrowKeys)override;
     sint getDirection(const uchar& key)override;
     void setDirection(const uchar& key, const size_t& cycle)override;
     void setName()override;
     void initializeCalculate()override { return; }
     string type()const override { return Player::HUMAN; }

};

#endif

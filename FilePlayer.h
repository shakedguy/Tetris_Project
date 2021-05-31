#pragma once
#include "Player.h"
#include "Computer_Player.h"
#include "HumanPlayer.h"
#include "Public_const_and_structs.h"
#include "Files_Handler.h"
#include "MyException.h"

using std::fstream;

class FilePlayer : virtual public Player
{

private:
    void getFromFile(Block& b);
    void initBornData(const size_t& cycle);
    void getNewBlock()override;

public:
    FilePlayer() : FilePlayer(0, { 0, 0 }, { 0, 0 }) {}
    FilePlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos,
        const size_t& cycle = 0);
    FilePlayer(const FilePlayer& _player, const size_t& cycle = 0);
    ~FilePlayer() {}
    void setDirection(const uchar& key, const size_t& cycle)override;
    void setName()override { return; }
    void initializeCalculate()override { return; }
    void setPlayerKeys(const string& arrowKeys)override { return; }
    sint getDirection(const uchar& key)override { return 0; }
    string type()const override { return Player::TEST; }
    

};


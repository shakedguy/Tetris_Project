/***************************************
     Header file for class "Computer Player" - Player's son.
***************************************/

#ifndef _COMPUTER_PLAYER_H_
#define _COMPUTER_PLAYER_H_
#include "Player.h"

class ComputerPlayer : public Player
{
    static constexpr size_t DIRECTION_CHECK = 2;
    static ushort level;
    enum Levels { BEST, GOOD, NOVICE };
    short steps, clockwise;
    short CounterClockwise = clockwise = steps = 0;
    array<ushort, DIRECTION_CHECK> directionCheck;
    

private:
     void calculateBestPos();
     Coordinate noRotateBlock();
     Coordinate oneRotateBlock();
     Coordinate threeRotateBlock();
     void checkLevel(Coordinate& bestPos)const;
     void levelGood(Coordinate& bestPos)const;
     void levelNovice(Coordinate& bestPos)const;
     Coordinate bomb();
     void makeRotateMove();
     bool checkLastDirections(const ushort& dir);
     void insertCurrentDirection();
     void cleanAndDeleteCalculation(Board* b, Block* temp)const;
     Coordinate findBestBombPosition(Board* b, Block* temp)const;
     Coordinate findBestPosition(Block* block, ushort& situations);
     size_t getPositionData(Board* b, Block* temp, size_t& oneToGo)const;
     Coordinate getMaxDamagedPosition(size_t& max, const size_t& current, const Coordinate& bestPos, const Coordinate& tempPos)const;
     size_t setLimit(const Block* block)const;
     const short& preferNotInterfere(Board* b, vector<Block>& options, vector<ushort>& optionStatus, Coordinate& bestPos)const;
     void checkFillRows(const Block& temp, Coordinate& bestPos, size_t& fullRows, size_t& maxFullRows,
          ushort& bestSituation, const ushort& situation);
     void checkOneToGo(Board* b, const Block& temp,
          const Coordinate& lowestPos, Coordinate& oneToGoPos, size_t& oneToGo, size_t& maxOneToGo,
          ushort& bestSituation, const ushort& situation, bool& flag);
     void checkLowest(vector<Block>& options, vector<ushort>& optionStatus, const Block& temp, Coordinate& lowestPos,
          const ushort& situation);


public:
     ComputerPlayer() : ComputerPlayer(0, { 0, 0 }, { 0, 0 }) {}
     ComputerPlayer(const ushort& _playerNum, const Coordinate& _boardPos, const Coordinate& _boxPos);
     ComputerPlayer(const ComputerPlayer& _ComputerPlayer) { *this = _ComputerPlayer; }
     ComputerPlayer& operator=(const ComputerPlayer& _player);
     ComputerPlayer* operator->() override { return this; }
     ComputerPlayer& operator*() { return *this; }
     sint getDirection(const uchar& key)override { return 0; }
     void setDirection(const uchar& key)override;
     void setName()override { return; }
     void setPlayerKeys(const string& arrowKeys)override { return; }
     void initializeCalculate()override { steps = 0; clockwise = CounterClockwise = 0; }
     static void setLevel(const ushort& _level) { level = _level; }
};

#endif
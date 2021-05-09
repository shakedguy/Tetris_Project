/***************************************
     Header file for class "Computer Player" - Player's son.
***************************************/

#ifndef _COMPUTER_PLAYER_H_
#define _COMPUTER_PLAYER_H_
#include "Player.h"

class ComputerPlayer : public Player
{
     enum Constants { INITIALIZE_STEPS = -Board::WIDTH, INITIALIZE_ROTATES = -1, DIRECTION_CHECK = 2 };
     enum Levels { BEST, GOOD, NOVICE };
     int steps = INITIALIZE_STEPS;
     short clockWise = INITIALIZE_ROTATES;
     short CounterClockWise = INITIALIZE_ROTATES;
     array<ushort, DIRECTION_CHECK> directionCheck;
     static ushort level;

private:
     void calculateBestPos();
     Point noRotateBlock();
     Point oneRotateBlock();
     Point threeRotateBlock();
     void checkLevel(Point& bestPos)const;
     Point bomb();
     void makeRotateMove();
     bool checkLastDirections(const ushort& dir);
     void insertCurrentDirection();
     void cleanAndDeleteCalculation(Board* b, Block* temp)const;
     Point findBestBombPosition(Board* b, Block* temp)const;
     Point findBestPosition(Block* block, short& situations)const;
     size_t getPositionData(Board* b, Block* temp, size_t& oneToGo)const;
     Point getMaxDamagedPosition(size_t& max, const size_t& current, const Point& bestPos, const Point& tempPos)const;
     size_t setLimit(const Block* block)const;
     Point preferNotInterfere(Board* b, vector<Block>& options)const;
     void positionsPriorities(const Board* b, vector<Block>& options, size_t& oneToGo, size_t& maxOneToGo,
          size_t& fullRows, size_t& maxFullRows, Point& bestPos, Point& lowestPos, const Block* temp, short& bestSituation, short& situation)const;


public:
     ComputerPlayer() : ComputerPlayer(0, { 0, 0 }, { 0, 0 }) {}
     ComputerPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos);
     ComputerPlayer(const ComputerPlayer& _ComputerPlayer) { *this = _ComputerPlayer; }
     ComputerPlayer& operator=(const ComputerPlayer& _player);
     sint getDirection(const uchar& key)override { return 0; }
     void setDirection(const uchar& key)override;
     void setName()override { return; }
     void setPlayerKeys(const string& arrowKeys)override { return; }
     void initializeCalculate()override { steps = INITIALIZE_STEPS; clockWise = CounterClockWise = INITIALIZE_ROTATES; }
     static void setLevel(const ushort& _level) { level = _level; }

     
    

};

#endif
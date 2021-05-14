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
     Point noRotateBlock();
     Point oneRotateBlock();
     Point threeRotateBlock();
     void moveRight();
     void moveLeft();
     void clockwiseRotate();
     void counterClockwiseRotate();
     void calculateRotates(const ushort& shape);
     void checkLevel(Point& bestPos)const;
     void levelGood(Point& bestPos)const;
     void levelNovice(Point& bestPos)const;
     Point bomb();
     void makeRotateMove();
     bool checkLastDirections(const ushort& dir);
     void insertCurrentDirection();
     void cleanAndDeleteCalculation(Board* b, Block* temp)const;
     Point findBestBombPosition(Board* b, Block* temp)const;
     Point findBestPosition(Block* block, ushort& situations);
     size_t getPositionData(Board* b, Block* temp)const;
     Point getMaxDamagedPosition(size_t& max, const size_t& current, const Point& bestPos, const Point& tempPos)const;
     size_t setLimit(const Block* block)const;
     Point preferNotInterfere(Board* b, vector<Block>& options, vector<ushort>& optionStatus,
         ushort& bestSituation, Point& lowestPos)const;
     void checkFillRows(const Block& temp, Point& bestPos, size_t& fullRows, size_t& maxFullRows,
         const ushort& situation, ushort& bestSituation);
     Point checkOneToGo(Board* b, const Block& temp, vector<Block>& options, vector<ushort>& optionStatus,
         ushort& bestSituation, Point& lowestPos)const;
          
     void checkLowest(vector<Block>& options, vector<ushort>& optionStatus, const Block& temp, Point& lowestPos,
          const ushort& situation);


public:
     ComputerPlayer() : ComputerPlayer(0, { 0, 0 }, { 0, 0 }) {}
     ComputerPlayer(const ushort& _playerNum, const Point& _boardPos, const Point& _boxPos);
     ComputerPlayer(const ComputerPlayer& _ComputerPlayer) { *this = _ComputerPlayer; }
     ComputerPlayer& operator=(const ComputerPlayer& _player);
     ComputerPlayer* operator->() override { return this; }
     ComputerPlayer& operator*() { return *this; }
     sint getDirection(const uchar& key)override { return 0; }
     void setDirection(const uchar& key)override;
     void setName()override { return; }
     void setPlayerKeys(const string& arrowKeys)override { return; }
     void initializeCalculate()override { steps = clockwise = CounterClockwise = 0; }
     static void setLevel(const ushort& _level) { level = _level; }
};

#endif
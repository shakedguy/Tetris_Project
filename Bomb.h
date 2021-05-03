#pragma once
#include "Block.h"
class Bomb : public Block
{
     enum Constants { BOMB = 149, EXPLOSION_RANGE = 4 };

     friend class Board;

public:
     Bomb(const uchar& _shape = BOMB) : Bomb(_shape, { 0,0 }) {}
     Bomb(const Point& _pos) :Bomb(BOMB, { 0,0 }) {}
     Bomb(const uchar& _shape, const Point& _pos);
     ~Bomb()override = default;
     void setFigure()override { figure[0][0] = shape; }
};


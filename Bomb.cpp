#include "Bomb.h"

Bomb::Bomb(const uchar& _shape, const Point& _pos)
{
     pos = _pos;
     shape = _shape;
     cleanBlock();
     figure[0][0] = 1;
}

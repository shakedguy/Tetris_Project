/***************************************
	Header file for class "Point".
***************************************/
#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>


using namespace std;

class Point
{
	int x, y;
	enum { UP, DOWN, LEFT, RIGHT };
public:
	Point(int _x = 0, int _y = 0):  x(_x), y(_y) {} 
	void draw(char ch);
	void move(int direction);
	void setPos(int _x, int _y) { x = _x; y = _y; }
	int getX() { return x; }
	int getY() { return y; }
};

#endif
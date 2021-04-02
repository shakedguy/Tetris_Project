/***************************************
	Header file for class "Brick".
***************************************/
#ifndef _MENU_H_
#define _MENU_H_
#include "Board.h"
#include "Point.h"

class Menu
{
	Point pos;
	Board menu[3];

private:
	void printMenuOptions();
public:
	Menu() :Menu({ 0,0 }) {}
	Menu(Point _pos);
	void drawMenu();
	unsigned int getOption();
};

#endif

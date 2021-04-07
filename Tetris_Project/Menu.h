﻿/***************************************
	Header file for class "Brick".
***************************************/
#ifndef _MENU_H_
#define _MENU_H_
#include "Board.h"
#include "Point.h"

class Menu
{
	Point pos;
	array<Board, BOXES_IN_MENU> menu;
	array<Block, BLOCKS_IN_MENU> blocks;

private:
	void printMenuOptions();
	void printMenuColor(const ushort& blockNum);
	void drawBlocksInMenu();
public:
	Menu() :Menu({ 0,0 }) {}
	Menu(Point _pos);
	~Menu() = default;
	void drawMenu();
	ushort getOption();
	Point getLastBoxPos() { return menu[menu.size() - 1].pos; }
};

#endif

/***************************************
	Header file for class "Brick".
***************************************/
#pragma once
#ifndef _MENU_H_
#define _MENU_H_
#include "Board.h"
#include "Point.h"

class Menu
{
	static bool colorsMode;
	Point pos;
	Board menu;
	//array<Board, BOXES_IN_MENU> menu;
	array<Block, BLOCKS_IN_MENU> blocks;
	friend class Game;

private:
	void printMenuOptions()const;
	void printMenuColor()const;
	void drawBlocksInMenu()const;
	void drawMenu()const;
	void setMenuBlock();
	void pickColor(const int& row)const;
	
public:
	Menu() :Menu({ 0,0 }) {}
	Menu(Point _pos);
	~Menu() = default;
	friend ostream& operator<<(ostream& out, const Menu& _menu) { _menu.drawMenu(); return out; }
	ushort getOption();
	Point getLastBoxPos() { return Point{ (int)menu.pos.getX(),(int)menu.pos.getY() + (int)menu.length }; }
	static void changeColorsMode();
	
};

#endif

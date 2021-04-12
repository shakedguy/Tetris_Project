/***************************************
	Header file for class "Menu".
***************************************/
#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include "Public_const_and_structs.h"
#include "Board.h"
#include "Point.h"

class Menu
{
	static bool colorsMode;
	Point pos;
	Board menu;
	array<Block, BLOCKS_IN_MENU> blocks;
	friend class Game;

private:
	void printMenuOptions() const;
	void printMenuColor() const;
	void drawBlocksInMenu() const;
	void drawMenu() const;
	void setMenuBlock();
	void pickColor(const int& row) const;

public:
	Menu() : Menu({0, 0}) {}
	Menu(Point _pos);
	~Menu() = default;

	friend std::ostream& operator<<(std::ostream& out, const Menu& _menu) {
		_menu.drawMenu();
		return out;
	}

	ushort getOption() { return _getch() - '0'; }

	Point getLastBoxPos() {
		return Point{
				static_cast<int>(menu.pos.getX()), static_cast<int>(menu.pos.getY()) + static_cast<int>(menu.length)
			};
	}

	static void changeColorsMode();
};

#endif

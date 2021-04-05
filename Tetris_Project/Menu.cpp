﻿#include "Menu.h"

Menu::Menu(Point _pos) : pos(_pos)
{
	for (int i = 0; i < menu.size(); i++)
	{
		menu[i].setPos(pos.getX(), pos.getY() + i * MENU_BLOCK_LENGTH + 1);
		menu[i].resizeBoundaries(MENU_BLOCK_WIDTH, MENU_BLOCK_LENGTH);
		menu[i].setAllBoundaries();
	}
}
void Menu::drawMenu()
{
	
	for (int i = 0; i < menu.size(); i++)
	{
		if (!i)
			setTextColor(GREEN);
		else if (i == 1)
			setTextColor(YELLOW);
		else if(i==2)
			setTextColor(LIGHTBLUE);
		else
			setTextColor(LIGHTRED);
		menu[i].drawBoard();
		printMenuColor(i);
	}
	setTextColor(WHITE);
	printMenuOptions();

}
void Menu::printMenuColor(const unsigned short& k)
{
	char ch = 178;
	for (int i = 1; i < menu[k].width - 1; i++)
	{
		for (int j = 1; j < menu[k].length - 1; j++)
		{
			gotoxy(menu[k].pos.getX() + i, menu[k].pos.getY() + j);
			cout << ch;
		}
	}
	
}

void Menu::printMenuOptions()
{
	gotoxy(menu[0].pos.getX() + 9, menu[0].pos.getY() + 2);
	cout << "For new game input - " << NEW_GAME_INPUT << endl;
	gotoxy(menu[1].pos.getX() + 3, menu[1].pos.getY() + 2);
	cout << "For resume to your game input - " << RESUME_GAME_INPUT << endl;
	gotoxy(menu[2].pos.getX() + 6, menu[2].pos.getY() + 2);
	cout << "For keys and instructions - " << KEYS_AND_INSTRUCTIONS << endl;
	gotoxy(menu[3].pos.getX() + 10, menu[3].pos.getY() + 2);
	cout << "For exit input - " << EXIT_GAME_INPUT << endl;

}

unsigned Menu::getOption()
{
	unsigned int in;
	gotoxy(menu[menu.size() - 1].pos.getX() + 20, menu[menu.size() - 1].pos.getY() + 6);
	cin >> in;
	clear_screen();
	return in;
}




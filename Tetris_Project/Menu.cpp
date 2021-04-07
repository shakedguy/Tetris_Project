﻿#include "Menu.h"

Menu::Menu(Point _pos) : pos(_pos)
{
	for (int i = 0; i < menu.size(); ++i)
	{
		menu[i].pos = { pos.getX(), pos.getY() + i * MENU_BLOCK_LENGTH + 1 };
		menu[i].resizeBoundaries(MENU_BLOCK_WIDTH, MENU_BLOCK_LENGTH);
		menu[i].setAllBoundaries();
	}
}
void Menu::drawMenu()
{

	for (size_t i = 0; i < menu.size(); ++i)
	{
#ifdef ___COLORS___
		if (!i)
			setTextColor(GREEN);
		else if (i == 1)
			setTextColor(YELLOW);
		else if (i == 2)
			setTextColor(LIGHTBLUE);
		else
			setTextColor(LIGHTRED);
#endif

		menu[i].drawBoard();
#ifdef ___COLORS___
		printMenuColor(i);
#endif
	}
#ifdef  ___COLORS___
	setTextColor(WHITE);
#endif
	printMenuOptions();
	drawBlocksInMenu();

}
void Menu::printMenuColor(const ushort& blockNum)
{
	for (size_t i = 1; i < menu[blockNum].width - 1; ++i)
	{
		for (size_t j = 1; j < menu[blockNum].length - 1; ++j)
		{
			gotoxy(menu[blockNum].pos.getX() + i, menu[blockNum].pos.getY() + j);
			cout << static_cast<uchar>(SHAPE_AFTER_FREEZE);
		}
	}
}

void Menu::printMenuOptions()
{
	gotoxy(menu[0].pos.getX() + 9, menu[0].pos.getY() + 2);
	cout << "For new game press - " << NEW_GAME_INPUT << endl;
	gotoxy(menu[1].pos.getX() + 3, menu[1].pos.getY() + 2);
	cout << "For resume to your game press - " << RESUME_GAME_INPUT << endl;
	gotoxy(menu[2].pos.getX() + 3, menu[2].pos.getY() + 2);
	cout << "For keys and instructions press - " << INSTRUCTIONS_AND_KEYS << endl;
	gotoxy(menu[3].pos.getX() + 10, menu[3].pos.getY() + 2);
	cout << "For exit press - " << EXIT_GAME_INPUT << endl;
}

ushort Menu::getOption()
{
	gotoxy(menu[menu.size() - 1].pos.getX() + 20, menu[menu.size() - 1].pos.getY() + 6);
	const uchar in = _getch();
	return in - '0';
}

void Menu::drawBlocksInMenu()
{
	for (int i = 0; i < blocks.size(); ++i)
	{
		if (i < (BLOCKS_IN_MENU / 3))
			blocks[i].pos = { menu[0].pos.getX() - 8, menu[0].pos.getY() + ((i + 1) * 5) };
		else if (i < (BLOCKS_IN_MENU / 3) * 2)
			blocks[i].pos = { menu[0].pos.getX() + 48, menu[0].pos.getY() + ((i - 3) * 5) };
		else if (i < (BLOCKS_IN_MENU / 3) * 3)
			blocks[i].pos = { menu[menu.size() - 1].pos.getX() + ((i - 8) * 13), menu[menu.size() - 1].pos.getY() + 8 };
		blocks[i].drawBlock();
	}
}





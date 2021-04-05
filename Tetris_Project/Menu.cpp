#include "Menu.h"

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
#ifdef ___COLORS___
		if (!i)
			setTextColor(GREEN);
		else if (i == 1)
			setTextColor(YELLOW);
		else if(i==2)
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
void Menu::printMenuColor(const unsigned short& k)
{
	for (int i = 1; i < menu[k].width - 1; i++)
	{
		for (int j = 1; j < menu[k].length - 1; j++)
		{
			gotoxy(menu[k].pos.getX() + i, menu[k].pos.getY() + j);
			cout << static_cast<char>(SHAPE_AFTER_FREEZE);
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

void Menu::drawBlocksInMenu()
{

	for (int i = 0; i < BLOCKS_IN_MENU; i++)
	{
		if (i < 4)
			blocks[i].setPos(menu[0].pos.getX() - 8, menu[0].pos.getY() + ((i + 1) * 5));
		else if (i < 8)
			blocks[i].setPos(menu[0].pos.getX() + 48, menu[0].pos.getY() + ((i - 3) * 5));
		else if (i < 12)
			blocks[i].setPos(menu[menu.size() - 1].pos.getX() + ((i-8)*13), menu[menu.size() - 1].pos.getY() + 8);
		blocks[i].drawBlock();
	}
	
}





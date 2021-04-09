#include "Menu.h"

Menu::Menu(Point _pos) : pos(_pos)
{
	menu.pos = _pos;
	menu.resizeBoundaries(MENU_BLOCK_WIDTH, 25);
	menu.setAllBoundaries();
	for (int i = 1; i < menu.length - 1; i++)
		if (i % 4 == 0)
			menu.setSeparators(i);
	setMenuBlock();
}

bool Menu::colorsMode = false;

void Menu::drawMenu() const
{

	if (colorsMode)
		setTextColor(YELLOW);
	cout << menu;
	
	if (colorsMode)
		printMenuColor();
	printMenuOptions();
	drawBlocksInMenu();
}

void Menu::printMenuColor() const
{
	for (size_t i = 1; i < menu.width - 1; ++i)
	{
		for (size_t j = 1; j < menu.length - 1; ++j)
		{
			gotoxy(menu.pos.getX() + i, menu.pos.getY() + j);
			if (j % 4 != 0)
			{
				pickColor(j);
				cout << static_cast<uchar>(SHAPE_AFTER_FREEZE);
				setTextColor(WHITE);
			}
		}
	}
}

void Menu::pickColor(const int& row)const
{
	if (row < MENU_BLOCK_LENGTH)
		setTextColor(GREEN);
	else if (row < (MENU_BLOCK_LENGTH - 1) * 2)
		setTextColor(BROWN);
	else if (row < (MENU_BLOCK_LENGTH - 1) * 3)
		setTextColor(MAGENTA);
	else if (row < (MENU_BLOCK_LENGTH - 1) * 4)
		setTextColor(DARKGREY);
	else if (row < (MENU_BLOCK_LENGTH - 1) * 5)
		setTextColor(BLUE);
	else if (row < (MENU_BLOCK_LENGTH - 1) * 6)
		setTextColor(LIGHTRED);
}

void Menu::printMenuOptions() const
{
	gotoxy(menu.pos.getX() + 9, menu.pos.getY() + 2);
	cout << "For new game press - " << NEW_GAME_INPUT << endl;
	gotoxy(menu.pos.getX() + 3, menu.pos.getY() + (MENU_BLOCK_LENGTH-1) + 2);
	cout << "For resume to your game press - " << RESUME_GAME_INPUT << endl;
	gotoxy(menu.pos.getX() + 4, menu.pos.getY() + ((MENU_BLOCK_LENGTH-1) * 2) + 2);
	cout << "For set players names press - " << SET_NAMES_INPUT << endl;
	gotoxy(menu.pos.getX() + 2, menu.pos.getY() + ((MENU_BLOCK_LENGTH - 1) * 4) + 2);
	cout << "For keys and instructions press - " << INSTRUCTIONS_AND_KEYS << endl;
	gotoxy(menu.pos.getX() + 11, menu.pos.getY() + ((MENU_BLOCK_LENGTH - 1) * 5) + 2);
	cout << "For exit press - " << EXIT_GAME_INPUT << endl;

	if(colorsMode)
	{
		gotoxy(menu.pos.getX() + 5, menu.pos.getY() + ((MENU_BLOCK_LENGTH - 1) * 3) + 2);
		cout << "For black and white press - " << COLOR_MODE_INPUT << endl;
	}
	else
	{
		gotoxy(menu.pos.getX() + 6, menu.pos.getY() + ((MENU_BLOCK_LENGTH - 1) * 3) + 2);
		cout << "For colors mode press - " << COLOR_MODE_INPUT << endl;
	}
}

ushort Menu::getOption()
{
	const uchar in = _getch();
	return in - '0';
}

void Menu::drawBlocksInMenu() const
{
	for (const Block& block : blocks)
		cout << block;
}

void Menu::setMenuBlock()
{
	for (int i = 0; i < blocks.size(); ++i)
	{
		if (i < (blocks.size() / 2))
			blocks[i].pos = {menu.pos.getX() - 8, menu.pos.getY() + ((i + 1) * 5)};
		else
			blocks[i].pos = {menu.pos.getX() + 48, menu.pos.getY() + ((i - 3) * 5)};
	}
}

void Menu::changeColorsMode()
{
	if (colorsMode)
		colorsMode = false;
	else
		colorsMode = true;
}


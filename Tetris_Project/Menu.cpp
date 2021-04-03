#include "Menu.h"

Menu::Menu(Point _pos) : pos(_pos)
{
	for (int i = 0; i < 3; i++)
	{
		menu[i].setPos(pos.getX(), pos.getY() + i * MENU_BLOCK_LENGTH + 1);
		menu[i].resizeBoundaries(MENU_BLOCK_WIDTH, MENU_BLOCK_LENGTH);
		menu[i].setAllBoundaries();
	}
}
void Menu::drawMenu()
{
	for (int i = 0; i < menu.size(); i++)
		menu[i].drawBoard();
	printMenuOptions();
}

void Menu::printMenuOptions()
{
	gotoxy(menu[0].pos.getX() + 10, menu[0].pos.getY() + 2);
	cout << "For new game input - " << NEW_GAME_INPUT << endl;
	gotoxy(menu[1].pos.getX() + 3, menu[1].pos.getY() + 2);
	cout << "For resume to your game input - " << RESUME_GAME_INPUT << endl;
	gotoxy(menu[2].pos.getX() + 10, menu[2].pos.getY() + 2);
	cout << "For exit input - " << EXIT_GAME_INPUT << endl;
}

unsigned Menu::getOption()
{
	unsigned int in;
	gotoxy(menu[2].pos.getX() + 20, menu[2].pos.getY() + 7);
	cin >> in;
	system("cls");
	return in;
}




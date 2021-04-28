#include "Game.h"

Game::Menu::Menu(const Point& _pos) : pos(_pos) {
	menu.pos = _pos;
	menu.resizeBoundaries(MENU_BLOCK_WIDTH, 25);
	menu.setAllBoundaries();
	for (int i = 1; i < menu.length - 1; i++)
		if (i % 4 == 0)
			menu.setSeparators(i);
	setMenuBlock();
}

void Game::Menu::drawMenu() const {

	if (Game::colorsMode)
		setTextColor(BROWN);
	cout << menu;

	if (Game::colorsMode)
		printMenuColor();
	printMenuOptions();
	drawBlocksInMenu();
}

void Game::Menu::printMenuColor() const {
	
	for (size_t i = 1; i < menu.width - 1; ++i) {
		for (size_t j = 1; j < menu.length - 1; ++j) {
			gotoxy(menu.pos.getX() + i, menu.pos.getY() + j);
			if (j % 4 != 0) {
				pickColor(j);
				cout << static_cast<uchar>(Block::SHAPE_AFTER_FREEZE);
				setTextColor(WHITE);
			}
		}
	}
}

// Selects a suitable color for the block
void Game::Menu::pickColor(const int& row) const {
	
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

void Game::Menu::printMenuOptions() const {
	
	gotoxy(menu.pos.getX() + NEW_GAME_X, menu.pos.getY() + TEXT_Y);
	cout << "For new game press - " << NEW_GAME << endl;
	gotoxy(menu.pos.getX() + RESUME_GAME_X, menu.pos.getY() + (MENU_BLOCK_LENGTH - 1) + TEXT_Y);
	cout << "For resume to your game press - " << RESUME_GAME << endl;
	gotoxy(menu.pos.getX() + SET_NAMES_X, menu.pos.getY() + ((MENU_BLOCK_LENGTH - 1) * 2) + TEXT_Y);
	cout << "For set players names press - " << SET_NAMES << endl;
	gotoxy(menu.pos.getX() + INSTRUCTIONS, menu.pos.getY() + ((MENU_BLOCK_LENGTH - 1) * 4) + TEXT_Y);
	cout << "For keys and instructions press - " << INSTRUCTIONS_AND_KEYS << endl;
	gotoxy(menu.pos.getX() + EXIT, menu.pos.getY() + ((MENU_BLOCK_LENGTH - 1) * 5) + TEXT_Y);
	cout << "For exit press - " << EXIT_GAME << endl;
	if (Game::colorsMode) {
		gotoxy(menu.pos.getX() + COLOR_MODE_ON, menu.pos.getY() + ((MENU_BLOCK_LENGTH - 1) * 3) + TEXT_Y);
		cout << "For black and white press - " << COLOR_MODE << endl;
	}
	else {
		gotoxy(menu.pos.getX() + COLOR_MODE_OF, menu.pos.getY() + ((MENU_BLOCK_LENGTH - 1) * 3) + TEXT_Y);
		cout << "For colors mode press - " << COLOR_MODE << endl;
	}
}

void Game::Menu::drawBlocksInMenu() const {
	for (const Block& block : blocks)
		cout << block;
}

// Sets locations of the menu blocks
void Game::Menu::setMenuBlock() {
	
	for (int i = 0; i < blocks.size(); ++i) {
		if (i < (blocks.size() / 2))
			blocks[i].pos = { menu.pos.getX() + LEFT_BLOCKS_DISTANCE,
		     menu.pos.getY() + ((i + 1) * VERTICAL_BLOCKS_DISTANCE) };
		else
			blocks[i].pos = { menu.pos.getX() + RIGHT_BLOCKS_DISTANCE,
		     menu.pos.getY() + ((i - 3) * VERTICAL_BLOCKS_DISTANCE) };
	}
}

Point Game::Menu::getLastBoxPos()const
{
	return Point{ static_cast<int>(menu.pos.getX()),
	    static_cast<int>(menu.pos.getY()) + static_cast<int>(menu.length) };
}

/* Print the menu page, check what option the users input and send to the right function
 * if the input is not valid prints a message.
 */
void Game::Menu::menuPage(Game& game)
{
	cout << game.menu;
	switch (game.menu.getOption()) {
	case NEW_GAME:
		clrscr();
		if (game.gameNumber)
			game.clearGame();
		game.init();
		break;
	case RESUME_GAME:
		if (game.resumeGame()) {
			clrscr();
			game.resetCurrentBlocksPos();
			game.run();
		}
		else
			menuPage(game);
		break;
	case SET_NAMES:
		clrscr();
		game.setNames();
		menuPage(game);
		break;
	case INSTRUCTIONS_AND_KEYS:
		keyAndInstructions();
		menuPage(game);
		break;
	case COLOR_MODE:
		game.changeColorsMode();
		clrscr();
		menuPage(game);
		break;
	case EXIT_GAME:
		clrscr();
		break;

	default:
		game.inputErrorMassage();
		break;
	}
}

void Game::Menu::keyAndInstructions() {
	clrscr();
	cout << "\tInstructions" << "\t\t\t\t\t     " << "Left player" << "  |  " << "Right player" << endl;
	cout << "\t----------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t\t\t  |" << endl;
	cout << "\tMove the block to the right with the key:" << "\t\t" << "d/D" << "\t  |\t" << "l/L" << endl;
	cout << "\tMove the block left with the key:" << "\t\t\t" << "a/A" << "\t  |\t" << "j/J" << endl;
	cout << "\tRotate the block clockwise with the key:" << "\t\t" << "w/W" << "\t  |\t" << "i/I" << endl;
	cout << "\tRotate the block counterclockwise with the key:" << "\t\t" << "s/S" << "\t  |\t" << "k/K" << endl;
	cout << "\tDropping the block with the key:" << "\t\t\t" << "x/X" << "\t  |\t" << "m/M" << endl << endl << endl;
	cout << "\tPress any key to return to the menu" << endl;
	_getch();
	clrscr();
}



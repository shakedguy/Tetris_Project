#include "Game.h"

Game::Menu::Menu(const Coordinate& _pos) : pos(_pos), menuPages{ pos,pos,pos } {

	for (Board& page : menuPages)
	{
		page.resizeBoundaries(MENU_BOARD_WIDTH, MENU_BOARD_LENGTH);
		page.initialEmptyCells();
	}
	setMenuBoard();
	setNewGameAndLevelsMenus();
	setMenuBlock();
}

bool Game::Menu::resumeGame = false;

void Game::Menu::setNewGameAndLevelsMenus()
{
	for (size_t i = 1; i < menuPages.size(); ++i)
	{
		menuPages[i].setAllBoundaries();
	     for (int j = 1; j < menuPages[i].length - 1; ++j)
	          if (j % 4 == 0)
	               menuPages[i].setSeparators(j);
	}
}
void Game::Menu::setMenuBoard()
{
	menuPages[0].setAllBoundaries();
	for (int i = 1; i < menuPages[0].length - 1; i++)
		if (i % 4 == 0)
			menuPages[0].setSeparators(i);
}

void Game::Menu::updateMenuBoard()
{
	if (Menu::resumeGame && menuPages[0].length == MENU_BOARD_LENGTH)
	{
		menuPages[0].resizeBoundaries(MENU_BOARD_WIDTH, MENU_BOARD_LENGTH + MENU_BLOCK_LENGTH - 1);
		menuPages[0].initialEmptyCells();
		setMenuBoard();

	}
	else if (!Menu::resumeGame && menuPages[0].length > MENU_BOARD_LENGTH)
	{
		menuPages[0].resizeBoundaries(MENU_BOARD_WIDTH, MENU_BOARD_LENGTH);
		menuPages[0].initialEmptyCells();
		setMenuBoard();
	}
}

void Game::Menu::drawPage(const ushort& pageNumber) const {

	if (Game::colorsMode)
		menuPages[pageNumber].drawBoard(BROWN);
	else
		menuPages[pageNumber].drawBoard();
	if (Game::colorsMode)
		paintBoxes(pageNumber);
	drawBlocksInMenu();
	printOptions(pageNumber);
}

void Game::Menu::printOptions(const ushort& pageNumber) const
{
	if (pageNumber == MAIN_MENU_PAGE)
		printMainMenuOptions();
	else
		(pageNumber == NEW_GAME_PAGE) ? printNewGamePageOptions() : printLevelsPageOptions();
}

void Game::Menu::paintBoxes(const ushort& pageNumber) const {

	for (size_t i = 1; i < menuPages[pageNumber].width - 1; ++i)
	{
		for (size_t j = 1; j < menuPages[pageNumber].length - 1; ++j)
		{
			gotoxy(menuPages[pageNumber].pos.getX() + i, menuPages[pageNumber].pos.getY() + j);
			if (j % 4 != 0) 
			{
				pickColor(j);
				cout << static_cast<uchar>(Block::SHAPE_AFTER_FREEZE);
			}
		}
	}
	setTextColor(WHITE);
}

// Selects a suitable color for the block
void Game::Menu::pickColor(const size_t& row) const {

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

void Game::Menu::printMainMenuOptions() const {

	ushort temp = 1;
	const int& x = menuPages[0].pos.getX();
	const int& y = menuPages[0].pos.getY();
	gotoxy(x + NEW_GAME_X, y + TEXT_Y);
	cout << "For new game press - " << NEW_GAME << endl;
	if (Menu::resumeGame)
	{
		gotoxy(x + RESUME_GAME_X, y + (MENU_BLOCK_LENGTH - 1) * (temp++) + TEXT_Y);
		cout << "For resume to your game press - " << RESUME_GAME << endl;
	}
	gotoxy(x + SET_NAMES_X, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
	cout << "For set players names press - " << SET_NAMES << endl;
	if (Game::colorsMode) {
		gotoxy(x + COLOR_MODE_ON, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
		cout << "For black and white press - " << COLOR_MODE << endl;
	}
	else {
		gotoxy(x + COLOR_MODE_OF, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
		cout << "For colors mode press - " << COLOR_MODE << endl;
	}
	gotoxy(x + INSTRUCTIONS, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
	cout << "For keys and instructions press - " << INSTRUCTIONS_AND_KEYS << endl;
	gotoxy(x + EXIT, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
	cout << "For exit press - " << EXIT_GAME << endl;

}

void Game::Menu::printNewGamePageOptions() const {

	ushort temp = 1;
	const int& x = menuPages[1].pos.getX();
	const int& y = menuPages[1].pos.getY();
	gotoxy(x + PRINT_H_H, y + TEXT_Y);
	cout << "For Human vs Human press - " << H_VS_H << endl;
	gotoxy(x + PRINT_H_C, y + (MENU_BLOCK_LENGTH - 1) * (temp++) + TEXT_Y);
	cout << "For Human vs Computer press - " << H_VS_C << endl;
	gotoxy(x + PRINT_C_C, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
	cout << "For Computer vs Computer press - " << C_VS_C << endl;
	if (Game::colorsMode) {
		gotoxy(x + COLOR_MODE_ON, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
		cout << "For black and white press - " << COLOR_MODE << endl;
	}
	else {
		gotoxy(x + COLOR_MODE_OF, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
		cout << "For colors mode press - " << COLOR_MODE << endl;
	}
	gotoxy(x + BACK, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
	cout << "For back to menuPages press - " << EXIT_GAME << endl;
}

void Game::Menu::printLevelsPageOptions() const {

	ushort temp = 1;
	const int& x = menuPages[2].pos.getX();
	const int& y = menuPages[2].pos.getY();
	gotoxy(x + PRINT_BEST, y + TEXT_Y);
	cout << "For level BEST press - " << BEST << endl;
	gotoxy(x + PRINT_GOOD, y + (MENU_BLOCK_LENGTH - 1) * (temp++) + TEXT_Y);
	cout << "For level GOOD press - " << GOOD << endl;
	gotoxy(x + PRINT_NOVICE, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
	cout << "For level NOVICE press - " << NOVICE << endl;
	if (Game::colorsMode) {
		gotoxy(x + COLOR_MODE_ON, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
		cout << "For black and white press - " << COLOR_MODE << endl;
	}
	else {
		gotoxy(x + COLOR_MODE_OF, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
		cout << "For colors mode press - " << COLOR_MODE << endl;
	}
	gotoxy(x + BACK, y + ((MENU_BLOCK_LENGTH - 1) * (temp++)) + TEXT_Y);
	cout << "For back to menuPages press - " << EXIT_GAME << endl;
}

void Game::Menu::drawBlocksInMenu() const {
	for (const Block& block : blocks)
		cout << block;
}

// Sets locations of the menuPages blocks
void Game::Menu::setMenuBlock() {

	for (int i = 0; i < blocks.size(); ++i) {
		if (i < (blocks.size() / 2))
			blocks[i].pos = { menuPages[0].pos.getX() + LEFT_BLOCKS_DISTANCE,
			menuPages[0].pos.getY() + (i * VERTICAL_BLOCKS_DISTANCE) + MENU_BLOCK_LENGTH / 2 };
		else
			blocks[i].pos = { menuPages[0].pos.getX() + RIGHT_BLOCKS_DISTANCE,
			menuPages[0].pos.getY() + ((i - 4) * VERTICAL_BLOCKS_DISTANCE) + MENU_BLOCK_LENGTH / 2 };
	}
}

/* Print the menuPages page, check what option the users input and send to the right function
 * if the input is not valid prints a message.
 */
void Game::Menu::mainMenuPage(Game& game)const
{
	drawPage(MAIN_MENU_PAGE);
	switch (getOption()) {
	case NEW_GAME:
		clrscr();
		if (game.gameNumber)
			game.clearGame();
		newGamePage(game);
		break;
	case RESUME_GAME:
		if (Menu::resumeGame) {
			clrscr();
			game.resetCurrentBlocksPos();
			game.run();
		}
		else {
		     inputErrorMassage();
		     mainMenuPage(game);
		}
		break;
	case SET_NAMES:
		clrscr();
		game.setNames();
		mainMenuPage(game);
		break;
	case INSTRUCTIONS_AND_KEYS:
		keyAndInstructions();
		mainMenuPage(game);
		break;
	case COLOR_MODE:
		game.changeColorsMode();
		mainMenuPage(game);
		break;
	case EXIT_GAME:
		clrscr();
		break;

	default:
		inputErrorMassage();
		mainMenuPage(game);
		break;
	}
}

void Game::Menu::newGamePage(Game& game)const
{
	drawPage(NEW_GAME_PAGE);
     switch (getOption())
     {
	case H_VS_H:
		clrscr();
		game.init(Menu::humanVShuman);
		break;
	case H_VS_C:
		clrscr();
		levelsPage(game, Menu::humanVShuman);
		break;
	case C_VS_C:
		clrscr();
		levelsPage(game, Menu::computerVScomputer);
		break;
	case COLOR_MODE:
		game.changeColorsMode();
		newGamePage(game);
		break;
	case EXIT_GAME:
		clrscr();
		mainMenuPage(game);
		break;

	default:
		inputErrorMassage();
		newGamePage(game);
		break;
     }
}


void Game::Menu::levelsPage(Game& game, const string& option)const
{
	drawPage(LEVELS_PAGE);
	switch (getOption())
	{
	case BEST:
		ComputerPlayer::setLevel(BEST);
		break;
	case GOOD:
		ComputerPlayer::setLevel(GOOD);
		break;
	case NOVICE:
		ComputerPlayer::setLevel(NOVICE);
		break;
	case COLOR_MODE:
		game.changeColorsMode();
		levelsPage(game, option);
		break;
	case EXIT_GAME:
		clrscr();
		newGamePage(game);
		return;

	default:
		inputErrorMassage();
		levelsPage(game, option);
		break;
	}
	clrscr();
	game.init(option);
}


void Game::Menu::keyAndInstructions()const
{
	clrscr();
	cout << "\tInstructions" << "\t\t\t\t\t     " << "Left player" << "  |  " << "Right player" << endl;
	cout << "\t----------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t\t\t  |" << endl;
	cout << "\tMove the block to the right with the key:" << "\t\t" << "d/D" << "\t  |\t" << "l/L" << endl;
	cout << "\tMove the block left with the key:" << "\t\t\t" << "a/A" << "\t  |\t" << "j/J" << endl;
	cout << "\tRotate the block clockwise with the key:" << "\t\t" << "w/W" << "\t  |\t" << "i/I" << endl;
	cout << "\tRotate the block counterclockwise with the key:" << "\t\t" << "s/S" << "\t  |\t" << "k/K" << endl;
	cout << "\tDropping the block with the key:" << "\t\t\t" << "x/X" << "\t  |\t" << "m/M" << endl << endl << endl;
	cout << "\tPress any key to return to the menuPages" << endl;
	_getch();
	clrscr();
}

void Game::Menu::inputErrorMassage()const
{
	gotoxy(pos.getX() + 2, pos.getY() + menuPages[0].length);
	cout << "Not in the options, please try again" << endl;
}



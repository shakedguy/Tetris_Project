/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"

Game::Game() : menu({MENU_BOARD_POS}), players{
				   {1, {LEFT_BOARD_POS}, {LEFT_BOX_POS}},
				   {2, {RIGHT_BOARD_POS}, {RIGHT_BOX_POS}}
			   } {
	setGameButtons();
}

void Game::setGameButtons() {

	const Point& temp = {SPEED_MODE_BUTTON_POS};
	int y = 0;
	for (int i = 0; i < buttons.size(); ++i) {

		buttons[i].resizeBoundaries(GAME_BUTTON_WIDTH, GAME_BUTTON_LENGTH);
		buttons[i].setAllBoundaries();
		buttons[i].pos = {temp.getX(), temp.getY() + (static_cast<int>(buttons[i].length) * i) + y++};
	}
}

/* Print the menu page, check what option the users input and send to the right function
 * if the input is not valid prints a message.
 */
void Game::menuPage() {
	cout << menu;
	switch (menu.getOption()) {
	case NEW_GAME_INPUT:
		clrscr();
		if (gameNumber)
			clearGame();
		init();
		break;
	case RESUME_GAME_INPUT:
		if (resumeGame()) {
			clrscr();
			players[0].setCurrentBlockPos({LEFT_CURRENT_BLOCK});
			players[1].setCurrentBlockPos({RIGHT_CURRENT_BLOCK});
			run();
		}
		else
			menuPage();
		break;
	case SET_NAMES_INPUT:
		clrscr();
		setNames();
		menuPage();
		break;
	case INSTRUCTIONS_AND_KEYS:
		clrscr();
		keyAndInstructions();
		if (_kbhit())
			uchar c = _getch();
		break;
	case COLOR_MODE_INPUT:
		changeColorsMode();
		clrscr();
		menuPage();
		break;
	case EXIT_GAME_INPUT:
		clrscr();
		break;

	default:
		inputErrorMassage();
		break;
	}
}

/* initialization the static class variables */
bool Game::speedMode = false;
bool Game::colorsMode = false;

void Game::changeColorsMode() {

	if (Game::colorsMode)
		Game::colorsMode = false;
	else
		Game::colorsMode = true;
	Menu::changeColorsMode();
	Player::changeColorsMode();
	Block::changeColorsMode();
}

void Game::inputErrorMassage() {
	clrscr();
	cout << menu;
	gotoxy(menu.getLastBoxPos().getX() + 2, menu.getLastBoxPos().getY());
	cout << "Not in the options, please try again" << endl;
	menuPage();
}

void Game::keyAndInstructions() {
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
	menuPage();
}

/* Checks if there is a game to return to */
bool Game::resumeGame() {
	
	clrscr();
	cout << menu;
	if (players[0].isLost() || players[1].isLost()) {
		gotoxy(menu.pos.getX() + 4, menu.pos.getY() + static_cast<int>(menu.menu.getLength()));
		cout << "The game ended, please try again" << endl;
		Sleep(1500);
		return false;
	}
	if (!gameNumber) {
		gotoxy(menu.pos.getX() + (menu.menu.getWidth() / 4) - 1,
			   menu.pos.getY() + static_cast<int>(menu.menu.getLength()));
		cout << "There is no open game" << endl;
		Sleep(1500);
		return false;
	}
	return true;
}

/* initialization new game and printing players boards */
void Game::init() {
	gameNumber++;
	players[0].setPlayerKeys(PLAYER_ONE_KEYS);
	players[1].setPlayerKeys(PLAYER_TWO_KEYS);
	cout << players[0] << players[1];
	drawButtons();
	run();
}

/* drawing the modes buttons */
void Game::drawButtons() {

	if (Game::colorsMode)
		setTextColor(RED);
	for (const Board& button : buttons)
		cout << button;
	if (Game::colorsMode)
		setTextColor(WHITE);
	printButtonsInfo();
}

void Game::printButtonsInfo() {

	Point& temp = buttons[0].pos;
	gotoxy(temp.getX() + 2, temp.getY() + 1);
	cout << "Speed";
	gotoxy(temp.getX() + 2, temp.getY() + 2);
	cout << "mode";
	gotoxy(temp.getX() + 2, temp.getY() + 3);
	cout << "press *";
	gotoxy(temp.getX() + 4, temp.getY() + 5);
	if (speedMode) {
		cout << "ON ";
	}
	else
		cout << "OFF ";

	gotoxy(temp.getX() + 2, temp.getY() + 7);
	cout << "Color";
	gotoxy(temp.getX() + 2, temp.getY() + 8);
	cout << "mode";
	gotoxy(temp.getX() + 2, temp.getY() + 9);
	cout << "press 4";
	gotoxy(temp.getX() + 4, temp.getY() + 11);
	if (Game::colorsMode) {
		cout << "ON ";
	}
	else
		cout << "OFF ";
}

/* The runing functions responsible for the course of the game,
 * receiving the input from the keyboard, decoding it and sending
 * it to the functions that perform the required actions */
void Game::run() {
	
	uchar key, temp, temp2; // use 2 to temps to prevent excessive steps (not DEFUALT steps) in one turn
	key = temp = temp2 = DEFAULT;
	
	do {
		
		key = avoidMultipleHits();
		directions(key);
		checkGameModes(key);
		avoidMultipleMoves(key, temp, temp2);
		move();
		printScores();
		Sleep(gameSpeed);
		if (speedMode)
			checkSpeedStatus();
		temp2 = temp;
		temp = key;
	}
	while (key != ESC && (!players[0].isLost()) && (!players[1].isLost()));
	if (isSomeoneLose())
		clrscr();
	menuPage();
	clrscr();
}

/* Checks if the received character belongs to one of the player's buttons */
void Game::directions(const uchar& key) {

	short dir = DEFAULT; // initialization the direction to the DEFAULT step
	if ((dir = players[0].getDirection(key)) != -1)
		players[0].setDirection(dir);
	else if ((dir = players[1].getDirection(key)) != -1)
		players[1].setDirection(dir);
}

/* Checks if the received character belongs to one of the mode's buttons */
void Game::checkGameModes(const uchar& key) {

	if (key == SPEED_MODE) {

		changeSpeedMode();
		returnLastSpeed();
	}
	else if (key - '0' == COLOR_MODE_INPUT)
		changeColorsMode();
	
	drawButtons();
}

/* The function is responsible for receiving input from the players and preventing multiple keystrokes,
 * returns the last character received */
uchar Game::avoidMultipleHits() {
	
	_flushall();
	uchar key = DEFAULT;
	if (_kbhit()) {
		key = _getch();
		for (int i = 0; i < 10 && key != ESC; i++) {
			if (_kbhit())
				key = _getch();
		}
	}
	_flushall();
	return key;
}

/* The function prevents the players from performing more than 2 non-default steps */
void Game::avoidMultipleMoves(uchar& key, const uchar& temp, const uchar& temp2) {
	
	if (temp == key && temp2 == key) {
		if (players[0].getDirection(key) != -1 && !players[0].isDown(key))
			players[0].setDirection(DEFAULT);
		else if (players[1].getDirection(key) != -1 && !players[1].isDown(key))
			players[1].setDirection(DEFAULT);
		key = players[0].getKey(DROP);
	}
}

/* if both players "lose" at the same time, the score determines and if the scores are equal, its a time gime */
bool Game::isSomeoneLose() {
	clrscr();
	bool p1 = players[0].isLost(), p2 = players[1].isLost();
	if (p1 && p2) {

		uint s1, s2;
		if ((s1 = players[0].getScore()) == (s2 = players[1].getScore()))
			winningMassage(TIE_GAME_CODE);
		else if (s1 > s2)
			winningMassage(0);
		else
			winningMassage(1);
		return true;
	}
	if (p1) {

		winningMassage(1);
		return true;
	}
	if (p2) {
		winningMassage(static_cast<ushort>(0));
		return true;
	}
	return false;
}

void Game::winningMassage(const ushort& flag) const {

	const Point temp = {WINNING_MASSAGE};
	gotoxy(temp.getX(), temp.getY());
	if (flag == TIE_GAME_CODE)
		cout << "\t\t\t\tTie game";
	else {
		cout << players[flag].getName() << " won with - " << players[flag].getScore();
		cout << " point! Congratulations!!!";
	}
	gotoxy(temp.getX() + 7, temp.getY() + 1);
	cout << "Press any key to return to the menu";
	_getch();
}

void Game::changeSpeedMode() {

	if (Game::speedMode)
		speedMode = false;
	else
		speedMode = true;
}

void Game::returnLastSpeed() {

	if(Game::speedMode)
		gameSpeed -= (accNum - 1) * ACCELERATION;// If the player changed more than one time during the game,
	else                                          //the speed will come back to the highest mode they got so far
		gameSpeed = GAME_SPEED;	
}

void Game::checkSpeedStatus() {

	if (players[0].checkSpeed(accNum) || players[1].checkSpeed(accNum))
		acceleration();
}

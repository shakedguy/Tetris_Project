﻿/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"



Game::Game() : menu({ Game::Menu::MENU_X,Game::Menu::MENU_Y }),
humanPlayers{ HumanPlayer{1, {LEFT_BOARD,BOARDS_Y}, {LEFT_BOX,BOXES_Y},PLAYER_ONE_KEYS},
			HumanPlayer{2, {RIGHT_BOARD,BOARDS_Y}, {RIGHT_BOX,BOXES_Y},PLAYER_TWO_KEYS} },
	computerPlayers{ ComputerPlayer{1, {LEFT_BOARD,BOARDS_Y}, {LEFT_BOX,BOXES_Y}},
				ComputerPlayer{2, {RIGHT_BOARD,BOARDS_Y}, {RIGHT_BOX,BOXES_Y}} }
{
	gameSpeed = GAME_SPEED;
	setGameButtons();
}

Game::~Game() 
{	
	gotoxy(Game::WINNING_MASSAGE_X, Game::WINNING_MASSAGE_Y);
	cout << "Hope you enjoyed :), see you next time!" << endl << endl << endl << endl;
}

void Game::setGameButtons() {

	const Coordinate& temp = {SPEED_X,SPEED_Y};
	int y = 0;
	for (int i = 0; i < buttons.size(); ++i) {

		buttons[i].resizeBoundaries(GAME_BUTTON_WIDTH, GAME_BUTTON_LENGTH);
		buttons[i].setBoardPos({ temp.getX(), temp.getY() + (buttons[i].getLength() * i) + y++ });
		buttons[i].initialEmptyCells();
		buttons[i].setAllBoundaries();
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
	Player::changeColorsMode();
	Board::changeColorsMode();
	Block::changeColorsMode();
}

/* initialization new game and printing players boards */
void Game::init(const string& option) {

	if (!initializePlayers(option))
		return;
	gameNumber++;
	cout << players[0] << players[1];
	drawButtons();
	run();

}

bool Game::initializePlayers(const string& option)
{

	if (!option.compare(Menu::humanVShuman))
	{
		players[0] = &humanPlayers[0];
		players[1] = &humanPlayers[1];
	}
	else if (!option.compare(Menu::humanVScomputer))
	{
		players[0] = &humanPlayers[0];
		players[1] = &computerPlayers[1];
	}
	else if (!option.compare(Menu::computerVScomputer))
	{
		players[0] = &computerPlayers[0];
		players[1] = &computerPlayers[1];
	}
	else
		return false;
	return true;
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

	const Coordinate& temp = buttons[0].getPos();
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
		resetIndicators();
	}
	while (key != ESC && (!players[0]->isLost()) && (!players[1]->isLost()));
	if (isSomeoneLose())
		clrscr();
	menu.updateMenuBoard();
	menu.mainMenuPage(*this);
	clrscr();
}

void Game::resetIndicators()
{
	players[0]->showIndicateHit(DEFAULT);
	players[1]->showIndicateHit(DEFAULT);
}


/* Checks if the received character belongs to one of the player's buttons */
void Game::directions(const uchar& key) {

	players[0]->setDirection(key);
	players[1]->setDirection(key);
}

/* Checks if the received character belongs to one of the mode's buttons */
void Game::checkGameModes(const uchar& key) {

	if (key == SPEED_MODE) {

		changeSpeedMode();
		returnLastSpeed();
	}
	else if (key - '0' == Menu::COLOR_MODE)
		changeColorsMode();
	drawButtons();
}

/* The function is responsible for receiving input from the players and preventing multiple keystrokes,
 * returns the last character received */
uchar Game::avoidMultipleHits()const {
	
	_flushall();
	uchar key = DEFAULT;
	if (_kbhit()) {
		key = _getch();
		for (int i = 0; i < HITS_LIMIT && key != ESC; ++i) {
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
		sint dir;
		if (typeid(*players[0]) == typeid(HumanPlayer) && (dir = players[0]->getDirection(key) != -1) && dir != DEFAULT/*!players[0]->isDown(key)*/)
			players[0]->setDirection(DEFAULT);
		else if (typeid(*players[1]) == typeid(HumanPlayer) && (dir = players[1]->getDirection(key) != -1) && dir != DEFAULT/*!players[1]->isDown(key)*/)
			players[1]->setDirection(DEFAULT);
		key = DEFAULT;
	}
}

/* if both players "lose" at the same time, the score determines and if the scores are equal, its a time gime */
bool Game::isSomeoneLose() {
	clrscr();
	bool p1 = players[0]->isLost(), p2 = players[1]->isLost();
	if (p1 && p2) {

		size_t s1, s2;
		if ((s1 = players[0]->getScore()) == (s2 = players[1]->getScore()))
			winningMassage(TIE_GAME_CODE);
		else if (s1 > s2)
			winningMassage(0);
		else
			winningMassage(1);
		Game::Menu::possibleResumeGame(false);
		return true;
	}
	if (p1) {

		winningMassage(1);
		Game::Menu::possibleResumeGame(false);
		return true;
	}
	if (p2) {
		winningMassage(static_cast<ushort>(0));
		Game::Menu::possibleResumeGame(false);
		return true;
	}
     Game::Menu::possibleResumeGame(true);
	return false;
}

void Game::winningMassage(const ushort& flag) const {

	const Coordinate temp = { Game::WINNING_MASSAGE_X,Game::WINNING_MASSAGE_Y };
	gotoxy(temp.getX(), temp.getY());
	if (flag == TIE_GAME_CODE)
		cout << "\t\t\t\tTie game";
	else {
		cout << players[flag]->getName() << " won with - " << players[flag]->getScore();
		cout << " point! Congratulations!!!";
	}
	gotoxy(temp.getX() + 7, temp.getY() + 1);
	cout << "Press any key to return to the menuPages";
	_getch();
}

void Game::changeSpeedMode() {

	if (Game::speedMode)
		Game::speedMode = false;
	else
		Game::speedMode = true;
}

void Game::returnLastSpeed() {

	if(Game::speedMode)
		Game::gameSpeed -= (accNum - 1) * ACCELERATION;// If the player changed more than one time during the game,
	else                                          //the speed will come back to the highest mode they got so far
		Game::gameSpeed = GAME_SPEED;
}

void Game::checkSpeedStatus() {

	if ((players[0]->checkSpeed(accNum) || players[1]->checkSpeed(accNum)) && gameSpeed > 20)
		acceleration();
}

void Game::resetCurrentBlocksPos()
{
	players[0]->setCurrentBlockPos({ Player::LEFT_BLOCK,Player::BLOCKS_Y });
	players[1]->setCurrentBlockPos({ Player::RIGHT_BLOCK,Player::BLOCKS_Y });
}

void Game::setNames()
{
	humanPlayers[0].setName();
	humanPlayers[1].setName();
}


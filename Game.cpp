/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"

Game::Game() : menu({ Game::Menu::MENU_X,Game::Menu::MENU_Y })
{
	setGameButtons();
}

Game::~Game() 
{
	for (Player* player : players)
		delete player;

	gotoxy(Game::WINNING_MASSAGE_X, Game::WINNING_MASSAGE_Y);
	cout << "Hope you enjoyed :), see you next time!" << endl << endl << endl << endl;
}

void Game::startGame(int argc, char* argv[])noexcept(false)
{
	clrscr();
	hideCursor();
	if (argc > 1)
	{
		try
		{
			openGameMode(argc, argv);
		}
		catch (CommandLineException& ex)
		{
			ex.errorMessage();
			throw;
		}
	}
	if (Game::gameMode == LOAD || Game::gameMode == SILENT)
		init("");
	else
		menu.mainMenuPage(*this);
}

void Game::openGameMode(int argc, char* argv[])noexcept(false)
{
	if (!strcmp(argv[1], SAVE_MODE))
		changeGameMode(Game::SAVE);
	else if (!strcmp(argv[1], Game::LOAD_MODE))
	{
		if (argc == 2)
			changeGameMode(Game::LOAD);
		else if (!strcmp(argv[2], Game::SILENT_MODE))
			changeGameMode(Game::SILENT);
	}
	else
		throw CommandLineException();
}

void Game::setGameButtons() {

	const Point& temp = {SPEED_X,SPEED_Y};
	int y = 0;
	for (int i = 0; i < buttons.size(); ++i) {

		buttons[i].resizeBoundaries(GAME_BUTTON_WIDTH, GAME_BUTTON_LENGTH);
		buttons[i].setPos(Point{ temp.getX(), y++ + (temp.getY() + buttons[i].getLength() * i)});
		buttons[i].initialEmptyCells();
		buttons[i].setAllBoundaries();
		buttons[i].setColor(RED);
	}
}

/* initialization the static class variables */
ushort Game::gameMode = 0;
bool Game::speedMode = false;
bool Game::colorsMode = false;
size_t Game::gameSpeed = GAME_SPEED;
size_t Game::accNum = 1;

void Game::acceleration()
{
	(Game::gameSpeed -= ACCELERATION >= MAX_SPEED) ? Game::gameSpeed -= ACCELERATION : MAX_SPEED;
	++accNum;
}



void Game::changeColorsMode() {

	if (Game::colorsMode)
		Game::colorsMode = false;
	else
		Game::colorsMode = true;
	Player::changeColorsMode();
	Board::changeColorsMode();
	Block::changeColorsMode();
}

void Game::clearGame()
{
	players[0]->clearGame();
	players[1]->clearGame();
	if (Game::speedMode)
		Game::changeSpeedMode();
}

void Game::resumeGame()
{
	clrscr();
	resetCurrentBlocksPos();
	drawButtons();
	cout << players[0] << players[1];
	run();
}



/* initialization new game and printing players boards */
void Game::init(const string& option)noexcept(false)
{
	try
	{
		initializePlayers(option);
	}
	catch (const std::bad_alloc& e)
	{
		e.what();
		throw;
	}
	++gameNumber;
	cout << players[0] << players[1];
	drawButtons();
	run();
}

void Game::initializePlayers(const string& option)noexcept(false)
{
	try
	{
		if (Game::gameMode == Game::LOAD || Game::gameMode == Game::SILENT)
			allocateFilePlayers();
		if (!option.compare(Menu::HUMAN_VS_HUMAN))
			allocateHumanPlayers();
		if (!option.compare(Menu::HUMAN_VS_COMPUTER))
			allocateHuman_VS_Computer();
		if (!option.compare(Menu::COMPUTER_VS_COMPUTER))
			allocateComputerPlayers();
	}
	catch (const std::bad_alloc& e)
	{
		e.what();
		throw;
	}
}

void Game::allocateComputerPlayers()noexcept(false)
{
	try
	{
		players[0] = new ComputerPlayer(1, { LEFT_BOARD,BOARDS_Y },
		{ LEFT_BOX,BOXES_Y });
		
		players[1] = new ComputerPlayer(2, { RIGHT_BOARD,BOARDS_Y },
			{ RIGHT_BOX,BOXES_Y });
	}
	catch (const std::bad_alloc& e)
	{
		e.what();
		throw;
	}
}

void Game::allocateFilePlayers()noexcept(false)
{
	try
	{
		players[0] = new FilePlayer({ 1, { LEFT_BOARD,BOARDS_Y },
											{ LEFT_BOX,BOXES_Y } });
		
		players[1] = new FilePlayer({ 2, { RIGHT_BOARD,BOARDS_Y },
											{ RIGHT_BOX,BOXES_Y } });
	}
	catch (const std::bad_alloc& e)
	{
		e.what();
		throw;
	}
}

void Game::allocateHumanPlayers()noexcept(false)
{
	try
	{
		players[0] = new HumanPlayer({ 1, { LEFT_BOARD,BOARDS_Y },
	{ LEFT_BOX,BOXES_Y }, PLAYER_ONE_KEYS });
		
		players[1] = new HumanPlayer({ 2, { RIGHT_BOARD,BOARDS_Y },
			{ RIGHT_BOX,BOXES_Y }, PLAYER_TWO_KEYS });
	}
	catch (const std::bad_alloc& e)
	{
		e.what();
		throw;
	}	
}

void Game::allocateHuman_VS_Computer()noexcept(false)
{
	try
	{
		players[0] = new HumanPlayer(1, { LEFT_BOARD,BOARDS_Y },
		{ LEFT_BOX,BOXES_Y }, PLAYER_ONE_KEYS);
		
		players[1] = new ComputerPlayer(2, { RIGHT_BOARD,BOARDS_Y },
			{ RIGHT_BOX,BOXES_Y });
	}
	catch (const std::bad_alloc& e)
	{
		e.what();
		throw;
	}
}

/* drawing the modes buttons */
void Game::drawButtons()
{
	if (Game::gameMode != Game::LOAD && Game::gameMode != Game::SILENT)
	{
		for (const Board& button : buttons)
			cout << button;
		printButtonsInfo();
	}
}

void Game::printButtonsInfo() {

	const Point& temp = buttons[0].getPos();
	gotoxy(temp.getX() + 2, temp.getY() + 1);
	cout << "Speed";
	gotoxy(temp.getX() + 2, temp.getY() + 2);
	cout << "mode";
	gotoxy(temp.getX() + 2, temp.getY() + 3);
	cout << "press *";
	gotoxy(temp.getX() + 4, temp.getY() + 5);
	if (Game::speedMode) {
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
		if ((Game::gameMode != Game::LOAD) && (Game::gameMode != Game::SILENT))
		{
			key = avoidMultipleHits();
			directions(key);
			avoidMultipleMoves(key, temp, temp2);
		}
		else
			directions(key);
		checkGameModes(key);
		printScores();
		try { move(); }
		catch (...) { break; }
		
		if (Game::gameMode != Game::SILENT)
			Sleep(/*Game::gameSpeed*/10);
		if (Game::speedMode)
			checkSpeedStatus();
		temp2 = temp;
		temp = key;
		++cycle;
		resetIndicators();
	} while (!endGame(key));
	continuePlaying();
}

void Game::continuePlaying()
{
	if (Game::gameMode != LOAD && Game::gameMode != SILENT)
	{
		if (isSomeoneLose())
			clrscr();
		
		menu.updateMenuBoard();
		menu.mainMenuPage(*this);
	}
	if(Game::gameMode==Game::SAVE && !endGame(NULL))
		result.printResult(players[0]->getPlayerNum(), cycle, players[0]->getHighestPointInBoard());
}


bool Game::endGame(const uchar& key) const
{
	if (players[0]->isLost() || players[1]->isLost())
		return true;
	if (key == ESC || players[0]->getDirection() == ESC || players[1]->getDirection() == ESC)
		return true;
	return false;
}


void Game::move()
{
	for (Player* player : players)
	{
		try { player->move(cycle); }
		catch (EndOfFileEx& ex)
		{
			if (checkResult(player->getPlayerNum(), player->getHighestPointInBoard()))
			{
				if (!player->isLost())
					ex.pausedGame(true);
				else
					ex.checkResult(true);
			}
			else
			{
				if (!player->isLost())
					ex.pausedGame(false);
				else
					ex.checkResult(false);
			}
			break;
		}
	}
}


void Game::resetIndicators()
{
	for (Player* player : players)
		player->showIndicateHit(DEFAULT);
}


/* Checks if the received character belongs to one of the player's buttons */
void Game::directions(uchar& key)
{
	for (Player* player : players)
	{
		try { player->setDirection(key, cycle); }
		catch (EndOfFileEx& ex)
		{
			if (checkResult(player->getPlayerNum(), player->getHighestPointInBoard()))
			{
				if (!player->isLost())
					ex.pausedGame(true);
				else
					ex.checkResult(true);
			}
			else
			{
				if (!player->isLost())
					ex.pausedGame(false);
				else
					ex.checkResult(false);
			}
			break;
		}
	}
}

bool Game::checkResult(const ushort& playerNum, const Point& highestPoint)
{
	size_t fileCycle;
	short filePlayerNum;
	Point filePoint;
	result.readResult(filePlayerNum, fileCycle, filePoint);
	if (fileCycle == cycle && filePlayerNum == playerNum && filePoint == highestPoint)
		return true;
	return false;
}


/* Checks if the received character belongs to one of the mode's buttons */
void Game::checkGameModes(const uchar& key) {

	if (key == SPEED_MODE || key - '0' == Menu::COLOR_MODE) {

		if(key == SPEED_MODE)
		{
			changeSpeedMode();
			returnLastSpeed();
		}
		else
			changeColorsMode();
		drawButtons();
	}
}

/* The function is responsible for receiving input from the players and preventing multiple keystrokes,
 * returns the last character received */
uchar Game::avoidMultipleHits()const {

	if (Game::gameMode == LOAD || Game::gameMode == SILENT)
		return DEFAULT;
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

	if (Game::gameMode == Game::LOAD || Game::gameMode == Game::SILENT)
		return;
	if (temp == key && temp2 == key) {
		sint dir;
		if (typeid(HumanPlayer) == typeid(*players[0]) &&
			((dir = players[0]->getDirection(key) != -1)) && dir != DEFAULT)
			players[0]->changeDirection(DEFAULT);
		else if (typeid(*players[1]) == typeid(HumanPlayer) &&
			(dir = players[1]->getDirection(key) != -1) && dir != DEFAULT)
			players[1]->changeDirection(DEFAULT);
		key = DEFAULT;
	}
}

/* if both players "lose" at the same time, the score determines and if the scores are equal, its a time gime */
bool Game::isSomeoneLose()
{
	clrscr();
	bool p1 = players[0]->isLost(), p2 = players[1]->isLost();
	if (p1 && p2)
		return tieGame();
	if (p1)
		return playerTowWon();
	if (p2)
		return playerOneWon();
     Game::Menu::possibleResumeGame(true);
	return false;
}

bool Game::tieGame()
{
	const size_t& score1 = players[0]->getScore(), score2 = players[1]->getScore();
	if (score1 == score2)
		winningMassage(-1);
	else if (score1 > score2)
		winningMassage(0);
	else
		winningMassage(1);
	Game::Menu::possibleResumeGame(false);
	return true;
}

bool Game::playerOneWon()
{
	winningMassage(static_cast<ushort>(0));
	Game::Menu::possibleResumeGame(false);
	const Point pos = players[0]->getHighestPointInBoard();
	return true;
}

bool Game::playerTowWon()
{
	winningMassage(1);
	Game::Menu::possibleResumeGame(false);
	const Point pos = players[1]->getHighestPointInBoard();
	return true;
}

void Game::winningMassage(const int& winner)
{
	const Point temp = { Game::WINNING_MASSAGE_X,Game::WINNING_MASSAGE_Y };
	gotoxy(temp.getX(), temp.getY());
	if (winner < 0)
		cout << "\t\t     Tie game";
	else {
		cout << players[winner]->getName() << " won with - " << players[winner]->getScore();
		cout << " point! Congratulations!!!";
	}
	if (winner >= 0)
		result.printResult(players[winner]->getPlayerNum(), cycle, players[winner]->getHighestPointInBoard());
	else
		result.printResult(-1, cycle, players[0]->getHighestPointInBoard());
	gotoxy(temp.getX()+3, temp.getY() + 4);
	cout << "Press any key to return to the menuPages";
	_getch();
}

void Game::changeSpeedMode() {

	if (Game::speedMode)
		Game::speedMode = false;
	else
		Game::speedMode = true;
}

void Game::returnLastSpeed()
{

	if (Game::speedMode && Game::accNum > 1)
		Game::gameSpeed -= (Game::accNum - 1) * ACCELERATION;// If the player changed more than one time during the game,
	else                                          //the speed will come back to the highest mode they got so far
		Game::gameSpeed = GAME_SPEED;
}

void Game::checkSpeedStatus()
{

	if ((players[0]->checkSpeed(Game::accNum) || players[1]->checkSpeed(Game::accNum))
		&& gameSpeed >= MAX_SPEED)
		acceleration();
}

void Game::resetCurrentBlocksPos()
{
	for (const Player* player : players)
		player->resetCurrentBlocksPos();
}

void Game::setNames()
{
	for (Player* player : players)
		if (typeid(*player) == typeid(HumanPlayer))
			player->setName();
}


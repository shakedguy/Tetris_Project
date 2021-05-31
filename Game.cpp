/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"

Game::Game() : menu({ Menu::objectsPositions::MENU_X,Menu::objectsPositions::MENU_Y })
{
	setGameButtons();
}

Game::~Game() 
{
	for (Player* player : players)
			delete player;
	
	if (Game::gameMode != Game_Modes::SILENT)
	{
		clrscr();
		gotoxy(Game::WINNING_MASSAGE_X, Game::WINNING_MASSAGE_Y);
		cout << "Hope you enjoyed :), see you next time!" << endl << endl << endl << endl;
	}
}

void Game::startGame(int argc, char* argv[])noexcept(false)
{
	clrscr();
	hideCursor();
	if (argc > 1)
	{
		try { openGameMode(argc, argv); }
		catch (CommandLineException& ex)
		{
			ex.errorMessage();
			throw;
		}
	}
	if (Game::gameMode == Game_Modes::LOAD || Game::gameMode == Game_Modes::SILENT)
		init("");
	else
		menu.mainMenuPage(*this);
}

void Game::openGameMode(int argc, char* argv[])noexcept(false)
{
	if (!strcmp(argv[1], SAVE_MODE))
		changeGameMode(Game_Modes::SAVE);
	else if (!strcmp(argv[1], Game::LOAD_MODE))
	{
		if (argc == 2)
			changeGameMode(Game_Modes::LOAD);
		else if (!strcmp(argv[2], Game::SILENT_MODE))
			changeGameMode(Game_Modes::SILENT);
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
	for(Player* player:players)
	{
		player->clearGame();
		delete player;
	}
	if (Game::speedMode)
		Game::changeSpeedMode();
	cycle = 0;
	result.clearGame();
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
	if (gameNumber)
		clearGame();
	++gameNumber;
	try { initializePlayers(option); }
	catch (const std::bad_alloc& e) { e.what(); throw; }
	clrscr();
	if (Game::gameMode != Game::SILENT) 
	{
		cout << players[0] << players[1];
		if (Game::gameMode != Game::LOAD)
			drawButtons();
	}
	run();
}

void Game::initializePlayers(const string& option)noexcept(false)
{
	try
	{
		if (Game::gameMode == Game_Modes::LOAD || Game::gameMode == Game_Modes::SILENT)
			allocateFilePlayers();
		else if (!option.compare(Menu::HUMAN_VS_HUMAN))
			allocateHumanPlayers();
		else if (!option.compare(Menu::HUMAN_VS_COMPUTER))
			allocateHuman_VS_Computer();
		else if (!option.compare(Menu::COMPUTER_VS_COMPUTER))
			allocateComputerPlayers();
	}
	catch (const std::bad_alloc& e) { e.what(); throw; }
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
	catch (const std::bad_alloc& e) { e.what(); throw; }
}

void Game::allocateFilePlayers()noexcept(false)
{
	try
	{
		players[0] = new FilePlayer( 1, { LEFT_BOARD,BOARDS_Y },
											{ LEFT_BOX,BOXES_Y } );
		
		players[1] = new FilePlayer( 2, { RIGHT_BOARD,BOARDS_Y },
											{ RIGHT_BOX,BOXES_Y } );
	}
	catch (const std::bad_alloc& e) { e.what(); throw; }
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
	catch (const std::bad_alloc& e) { e.what(); throw; }
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
	catch (const std::bad_alloc& e) { e.what(); throw; }
}

/* drawing the modes buttons */
void Game::drawButtons()
{
	if (Game::gameMode != Game_Modes::LOAD && Game::gameMode != Game_Modes::SILENT)
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
void Game::run()
{
	uchar prev, prevPrev; // use 2 to temps to prevent excessive steps (not DEFUALT steps) in one turn
	uchar key = prev = prevPrev = DEFAULT;
	
	do {
		if ((Game::gameMode != Game_Modes::LOAD) && (Game::gameMode != Game_Modes::SILENT))
			enableUserInput(key, prev, prevPrev);
		try { directions(key); }
		catch (...) { key = ESC; }
		checkGameModes(key);
		if (Game::gameMode != Game_Modes::SILENT)
			printScores();
		try { move(); }
		catch (...) { key = ESC; }

		if (Game::gameMode != Game::SILENT)
			Sleep(/*Game::gameSpeed*/20);
		if (Game::speedMode)
			checkSpeedStatus();
		resetIndicators();
		++cycle;
	} while (!endGame(key));
	continuePlaying();
}

void Game::enableUserInput(uchar& key, uchar& prev, uchar& prevPrev)
{
	key = avoidMultipleHits();
	avoidMultipleMoves(key, prev, prevPrev);
	prevPrev = prev;
	prev = key;
}

void Game::continuePlaying()
{
	if (Game::gameMode != Game_Modes::LOAD && Game::gameMode != Game_Modes::SILENT)
	{
		clrscr();
		menu.updateMenuBoard();
		menu.mainMenuPage(*this);
	}
	else
		testResult();
}

void Game::testResult()
{
	short winner = getWinner();

	if ((winner == players[0]->getPlayerNum()-1 || winner == players[1]->getPlayerNum()-1) &&
		onePlayerResult(winner))
		testResultMessage(true);
	else if (towPlayersResult(winner))
		testResultMessage(true);
	else
		testResultMessage(false);
}

void Game::testResultMessage(bool flag) const
{
	clrscr();
	gotoxy(WINNING_MASSAGE_X, WINNING_MASSAGE_Y);
	if (flag)
		cout << "Successful test";
	else
		cout << "Failed test";
	gotoxy(WINNING_MASSAGE_X - 9, WINNING_MASSAGE_Y + 1);
	cout << "Press any key to return to exit test";
	_getch();
	clrscr();
}



short Game::getWinner()
{
	bool p1 = players[0]->isLost(), p2 = players[1]->isLost();
	if (p1 && p2 && (players[0]->getScore() == players[1]->getScore()))
		return Constants::TIE_GAME;
	if (p1)
		return players[1]->getPlayerNum()-1;
	if (p2)
		return players[0]->getPlayerNum()-1;
	return Constants::INCOMPLETED;
}

bool Game::endGame(const uchar& key)
{
	if (isSomeoneLose())
		return true;
	if (key == ESC)
		return paused();
	return false;
}

void Game::move()
{
	for (Player* player : players)
	{
		try { player->move(cycle); }
		catch (BlocksFileEndEx& ex) { throw; }
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
		catch (BlocksFileEndEx& ex)
		{
			
			if (players[0]->isMovesEndOfFiles() && players[1]->isMovesEndOfFiles())
				throw;
		}
	}
}

void Game::isEndOfFiles()const
{
	if (players[0]->isEndOfFiles() && players[1]->isEndOfFiles())
		throw MyException();
}


bool Game::onePlayerResult(const short& winner)
{
	const Point& highestPoint = players[winner]->getHighestPointInBoard();
	size_t fileCycle;
	short filePlayerNum;
	Point filePoint;
	result.readOnePlayerResult(filePlayerNum, fileCycle, filePoint);
	//clrscr();
	//cout << "game:" << endl << cycle << " -> " << winner+1 << " -> ("
	//	<< highestPoint.getX() << "," << highestPoint.getY() << ")" << endl;
	//cout << "file:" << endl << fileCycle << " -> " << filePlayerNum << " -> ("
	//	<< filePoint.getX() << "," << filePoint.getY() << ")" << endl;
	//_getch();
	if (fileCycle != cycle && fileCycle + 1 != cycle && fileCycle - 1 != cycle)
		return false;
	if (filePlayerNum == winner+1 && filePoint == highestPoint)
		return true;
	return false;
}

bool Game::towPlayersResult(const short& gameResult)
{
	short fileResult;
	size_t fileCycle;
	Point first, second;
	result.readTowPlayersResult(fileResult, fileCycle, first, second);
	//clrscr();
	//gotoxy(WINNING_MASSAGE_X, WINNING_MASSAGE_Y);
	//cout << "game:" << endl << gameResult << " -> " << cycle << " -> ("
	//	<< players[0]->getHighestPointInBoard().getX() << "," << players[0]->getHighestPointInBoard().getY() <<
	//	")" << " -> (" << players[1]->getHighestPointInBoard().getX() << "," << players[1]->getHighestPointInBoard().getY() <<
	//	")"<<endl;
	//cout << "file:" << endl << fileResult << " -> " << fileCycle << " -> ("
	//	<< first.getX() << "," << first.getY() <<
	//	")" << " -> (" << second.getX() << "," << second.getY() << ")" << endl;
	//_getch();
	if (fileCycle != cycle && fileCycle + 1 != cycle && fileCycle - 1 != cycle)
		return false;
	if (fileResult == gameResult &&
		first == players[0]->getHighestPointInBoard() &&
		second == players[1]->getHighestPointInBoard())
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

	if (Game::gameMode == Game_Modes::LOAD || Game::gameMode == Game_Modes::SILENT)
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

bool Game::paused()
{
	if (Game::gameMode == Game_Modes::SAVE)
	{ 
		result.printTowPlayerResult(Constants::INCOMPLETED, cycle,
		players[0]->getHighestPointInBoard(), players[1]->getHighestPointInBoard());
		for (Player* player : players)
			player->printDataToFile();
	}
	return true;
}


bool Game::tieGame()
{

	const size_t& score1 = players[0]->getScore(), score2 = players[1]->getScore();
	if (score1 == score2)
	{
		if (Game::gameMode == Game_Modes::SAVE)
			saveNoWinnerGame(Constants::TIE_GAME);
		if (Game::gameMode != Game_Modes::LOAD && Game::gameMode != Game_Modes::SILENT)
			winningMassage(Constants::TIE_GAME);
	}
	else if (score1 > score2)
		return playerOneWon();
	else
		return playerTowWon();
	Game::Menu::possibleResumeGame(false);
	return true;
}

void Game::saveNoWinnerGame(const short& gameResult)
{
	result.printTowPlayerResult(gameResult, cycle,
		players[0]->getHighestPointInBoard(), players[1]->getHighestPointInBoard());
	for (Player* player : players)
		player->printDataToFile();
}

void Game::saveGame(const short& winner)
{
	result.printOnePlayerResult(winner, cycle,
		players[winner - 1]->getHighestPointInBoard());
	for (Player* player : players)
		player->printDataToFile();
}



bool Game::playerOneWon()
{
	if (Game::gameMode == Game_Modes::SAVE)
		saveGame(players[0]->getPlayerNum());
	if (Game::gameMode != Game_Modes::LOAD && Game::gameMode != Game_Modes::SILENT)
		winningMassage(players[0]->getPlayerNum());
	Game::Menu::possibleResumeGame(false);
	return true;
}

bool Game::playerTowWon()
{
	if (Game::gameMode == Game_Modes::SAVE)
		saveGame(players[1]->getPlayerNum());
	if (Game::gameMode != Game_Modes::LOAD && Game::gameMode != Game_Modes::SILENT)
		winningMassage(players[1]->getPlayerNum());
	Game::Menu::possibleResumeGame(false);
	return true;
}

void Game::winningMassage(const int& winner)
{
	clrscr();
	const Point temp = { Game::WINNING_MASSAGE_X,Game::WINNING_MASSAGE_Y };
	gotoxy(temp.getX(), temp.getY());
	if (winner == Constants::TIE_GAME)
		cout << "\t\t     Tie game";
	else 
	{
		cout << players[winner-1]->getName() << " won with - " << players[winner-1]->getScore();
		cout << " point! Congratulations!!!";
	}
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


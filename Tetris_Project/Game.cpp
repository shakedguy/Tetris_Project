/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"

Game::Game() : menu({ MENU_BOARD_POS }), players{ {1,{LEFT_BOARD_POS},{LEFT_BOX_POS}},
	{2,{RIGHT_BOARD_POS},{RIGHT_BOX_POS}} } {

	speedButton.resizeBoundaries(10, 5);
	speedButton.setAllBoundaries();
	speedButton.pos = { players[1].boardPos.getX() + (int)players[1].board.width + 25,players[1].boardPos.getY() + 4 };
}


void Game::menuPage()
{
	cout << menu;
	switch (menu.getOption())
	{
	case NEW_GAME_INPUT:
		clrscr();
		if (gameNumber)
			clearGame();
		init();
		break;
	case RESUME_GAME_INPUT:
		if (resumeGame())
		{
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

ushort Game::gameSpeed = GAME_SPEED;

ushort Game::accNum = 1;

bool Game::speedMode = false;

void Game::changeColorsMode()
{
	Menu::changeColorsMode();
	Player::changeColorsMode();
	Block::changeColorsMode();
}

void Game::inputErrorMassage()
{
	gotoxy(menu.getLastBoxPos().getX() + 2, menu.getLastBoxPos().getY());
	cout << "Not in the options, please try again" << endl;
	menuPage();
}

void Game::keyAndInstructions()
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
	cout << "\tPress any key to return to the menu" << endl;
	_getch();
	clrscr();
	menuPage();
}

bool Game::resumeGame()
{
	if (players[0].isLost() || players[1].isLost())
	{
		gotoxy(menu.pos.getX() + 4, menu.pos.getY() + static_cast<int>(menu.menu.getLength()));
		cout << "The game ended, please try again" << endl;
		Sleep(1500);
		return false;
	}
	if (!gameNumber)
	{
		gotoxy(menu.pos.getX() + (menu.menu.getWidth() / 4) - 1, menu.pos.getY() + static_cast<int>(menu.menu.getLength()));
		cout << "There is no open game" << endl;
		Sleep(1500);
		return false;
	}
	return true;
}

void Game::init()
{
	gameNumber++;
	players[0].setPlayerKeys(PLAYER_ONE_KEYS);
	players[1].setPlayerKeys(PLAYER_TWO_KEYS);
	cout << players[0] << players[1];
	if (Player::colorsMode)
		setTextColor(RED);
	cout << speedButton;
	if (Player::colorsMode)
		setTextColor(WHITE);
	gotoxy(speedButton.pos.getX() + 1, speedButton.pos.getY() + 1);
	cout << "Speed";
	gotoxy(speedButton.pos.getX() + 1, speedButton.pos.getY() + 2);
	cout << "mode";
	gotoxy(speedButton.pos.getX() + 1, speedButton.pos.getY() + 3);
	cout<<"press *";
	run();
}

void Game::run()
{
	uchar key, temp, temp2;
	key = temp = temp2 = DEFAULT;
	short dir = DEFAULT;
	do
	{
		key = avoidMultipleHits();
		if ((dir = players[0].getDirection(key)) != -1)
			players[0].setDirection(dir);
		else if ((dir = players[1].getDirection(key)) != -1)
			players[1].setDirection(dir);
		else if (key == SPEED_MODE)
			changeSpeedMode();
			
		avoidMultipleMoves(key, temp, temp2);
		move();
		returnDown();
		printScores();
		temp2 = temp;
		temp = key;
		Sleep(gameSpeed);
		if (Game::speedMode)
			checkSpeedStatus();
	}
	while (key != ESC && (!players[0].isLost()) && (!players[1].isLost()));
	if (isSomeoneLose())
		clrscr();
	menuPage();
	clrscr();
}

uchar Game::avoidMultipleHits()
{
	uchar key = DEFAULT;
	if(_kbhit())
	{
		key = _getch();
		for (int i = 0; i < 10 && key != ESC; i++)
		{
			_flushall();
			if (_kbhit())
				key = _getch();
		}
	}
	_flushall();
	return key;
}

void Game::avoidMultipleMoves(uchar& key, const uchar& temp, const uchar& temp2)
{
	if (temp == key && temp2 == key)
	{
		if (players[0].getDirection(key) != -1 && !players[0].isDown(key))
			players[0].setDirection(DEFAULT);
		else if (players[1].getDirection(key) != -1 && !players[1].isDown(key))
			players[1].setDirection(DEFAULT);
		key = players[0].getKey(DROP);
	}
}

bool Game::isSomeoneLose()
{
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
	if(p1) {
		
		winningMassage(1);
		return true;
	}
	if(p2) {
		winningMassage(static_cast<ushort>(0));
		return true;
	}
	return false;
}

void Game::winningMassage(const ushort& flag)const {

	const Point temp = { WINNING_MASSAGE };
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

	if (Game::speedMode) {

		speedMode = false;
		gameSpeed = GAME_SPEED;
	}
	else
		speedMode = true;	
}

void Game::checkSpeedStatus() {

	if (players[0].checkSpeed(accNum) || players[1].checkSpeed(accNum)) 
		acceleration();
}

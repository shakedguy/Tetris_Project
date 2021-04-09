/***************************************
	cpp file for class "Game".
***************************************/
#include "Game.h"


void Game::menuPage()
{
	cout << menu;
	switch (menu.getOption())
	{
	case NEW_GAME_INPUT:
		clear_screen();
		if (gameNumber)
			clearGame();
		init();
		break;
	case RESUME_GAME_INPUT:
		if (resumeGame())
		{
			clear_screen();
			players[0].setCurrentBlockPos({LEFT_CURRENT_BLOCK});
			players[1].setCurrentBlockPos({RIGHT_CURRENT_BLOCK});
			run();
		}
		else
			menuPage();
		break;
	case SET_NAMES_INPUT:
		clear_screen();
		setNames();
		menuPage();
		break;
	case INSTRUCTIONS_AND_KEYS:
		clear_screen();
		keyAndInstructions();
		if (_kbhit())
			uchar c = _getch();
		break;
	case COLOR_MODE_INPUT:
		changeColorsMode();
		clear_screen();
		menuPage();
		break;
	case EXIT_GAME_INPUT:
		clear_screen();
		break;
		
		default:
			inputErrorMassage();
			break;
	}
}

void Game::changeColorsMode()
{
	Menu::changeColorsMode();
	Player::changeColorsMode();
	Block::changeColorsMode();
}

void Game::inputErrorMassage()
{
	gotoxy(menu.getLastBoxPos().getX() + 2, menu.getLastBoxPos().getY() + 6);
	cout << "Not in the options, please try again" << endl;
	menuPage();
}

void Game::keyAndInstructions()
{
	clear_screen();
	cout << "\tInstructions" << "\t\t\t\t\t     " << "Left player" << "  |  " << "Right player" << endl;
	cout << "\t----------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t\t\t  |" << endl;
	cout << "\tMove the block to the right with the key:" << "\t\t" << "d/D" << "\t  |\t" << "l/L" << endl;
	cout << "\tMove the block left with the key:" << "\t\t\t" << "a/A" << "\t  |\t" << "j/J" << endl;
	cout << "\tRotate the block clockwise with the key:" << "\t\t" << "w/W" << "\t  |\t" << "i/I" << endl;
	cout << "\tRotate the block counterclockwise with the key:" << "\t\t" << "s/S" << "\t  |\t" << "k/K" << endl;
	cout << "\tDropping the block with the key:" << "\t\t\t" << "x/X" << "\t  |\t" << "m/M" << endl << endl << endl;
	cout << "\tEnter any key for back to menu" << endl;
	uchar key = _getch();
	clear_screen();
	menuPage();
}

bool Game::resumeGame()
{
	
	if (players[0].isLost() || players[1].isLost())
	{
		gotoxy(menu.pos.getX() + 4, menu.pos.getY() + (int)menu.menu.getLength());
		cout << "The game ended, please try again" << endl;
		Sleep(1500);
		return false;
	}
	if (!gameNumber)
	{
		gotoxy(menu.pos.getX() + (menu.menu.getWidth() / 4) - 1, menu.pos.getY() + (int)menu.menu.getLength());
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
	run();
}

void Game::run()
{
	uchar key = DEFAULT, temp = DEFAULT, temp2 = DEFAULT;
	short dir = DEFAULT;
	do
	{
		key = avoidMultipleHits();
		if ((dir = players[0].getDirection(key)) != -1)
			players[0].setDirection(dir);
		else if ((dir = players[1].getDirection(key)) != -1)
			players[1].setDirection(dir);
		avoidMultipleMoves(key, temp, temp2);
		move();
		returnDown();
		printScores();
		temp2 = temp;
		temp = key;
		Sleep(200);
	}
	while (key != ESC && (!players[0].isLost()) && (!players[1].isLost()));
	if (winningMassage())
		clear_screen();
	menuPage();
	
#ifndef  ___COLOR___
#define ___COLOR___
	setTextColor(WHITE);
#endif
	clear_screen();
}

uchar Game::avoidMultipleHits()
{
	uchar key = DEFAULT;
	if(_kbhit())
	{
		key = _getch();
		for (int i = 0; i < 10 && key != ESC; i++)
			if (_kbhit())
				key = _getch();
	}
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

bool Game::winningMassage()
{
	clear_screen();
	gotoxy(WINNING_MASSAGE);
	if (players[0].isLost())
	{
		cout << "Congratulations " << players[1].getName() << ", you won with "
		<< players[1].getScore() << " points !" << endl;
		Sleep(1500);
		return true;
	}
	if (players[1].isLost())
	{
		cout << "Congratulations " << players[0].getName() << ", you won with"
		<< players[0].getScore() << " points !" << endl;
		Sleep(1500);
		return true;
	}
	return false;
}

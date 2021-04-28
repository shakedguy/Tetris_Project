/***************************************
	Header file for class "Game".
***************************************/
#ifndef _GAME_H_
#define _GAME_H_

#include "Public_const_and_structs.h"
#include "Board.h"
#include "Menu.h"
#include "Player.h"


class Game
{
	static bool colorsMode;
	static bool speedMode;
	ushort accNum = 1;
	array<Board, GAME_BUTTONS> buttons;
	ushort gameSpeed = GAME_SPEED;
	Menu menu;
	Player players[NUM_OF_PLAYERS];
	ushort gameNumber = 0;

private:
	uchar avoidMultipleHits();
	void move() { players[0].move(); players[1].move(); }
	void drawBoards() const { players[0].drawBoard();	players[1].drawBoard(); }
	void printScores() const { players[0].printScore(); players[1].printScore(); }
	void clearGame() { players[0].clearGame();	players[1].clearGame(); }
	bool isSomeoneLose();
	bool resumeGame();
	void avoidMultipleMoves(uchar& key, const uchar& temp1, const uchar& temp2);
	void keyAndInstructions();
	void setNames() { players[0].setName();	players[1].setName(); }
	void inputErrorMassage();
	void changeColorsMode();
	void winningMassage(const ushort& flag) const;
	void checkSpeedStatus();
	void setGameButtons();
	void printButtonsInfo();
	void checkGameModes(const uchar& key);
	void directions(const uchar& key);
	void returnLastSpeed();

public:
	Game();
	~Game() = default;
	static void changeSpeedMode();
	void drawButtons();
	void acceleration() { gameSpeed -= ACCELERATION; accNum++; }
	void menuPage();
	void init();
	void run();

	
};

#endif

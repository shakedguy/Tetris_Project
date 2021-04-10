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
	static bool speedMode;
	static ushort gameSpeed;
	static ushort accNum;
	Menu menu;
	Player players[2];
	ushort gameNumber = 0;
	Board speedButton;

	friend class Player;

private:
	uchar avoidMultipleHits();
	void returnDown() { players[0].setDirection(DEFAULT); players[1].setDirection(DEFAULT); }
	void drawBoards()const { players[0].drawBoard(); players[1].drawBoard(); }
	void printScores()const { players[0].printScore(); players[1].printScore(); }
	void clearGame() { players[0].clearGame(); players[1].clearGame(); }
	bool isSomeoneLose();
	bool resumeGame();
	void avoidMultipleMoves(uchar& key, const uchar& temp1, const uchar& temp2);
	void keyAndInstructions();
	void setNames() { players[0].setName(); players[1].setName(); }
	void inputErrorMassage();
	void changeColorsMode();
	void winningMassage(const ushort& flag)const;
	void checkSpeedStatus();
	static void changeSpeedMode();
	static void acceleration() { gameSpeed -= 30; accNum++; }
	
public:
	Game(); 
	~Game() = default;
	void menuPage();
	void init();
	void run();
	void move() { players[0].move(); players[1].move(); }
	
	
};

#endif

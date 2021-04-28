/***************************************
 
	Guy Shaked - 205717952 
	Gur shmuelevitz - 207423625
	Main file - Tetris game
	
***************************************/

#include "Game.h"


int main() {

	hideCursor();
	Game game;
	game.startGame();
	gotoxy(WINNING_MASSAGE);
	cout << "Hope you enjoyed :), see you next time!" << endl << endl << endl << endl;
}

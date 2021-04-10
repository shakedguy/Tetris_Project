/***************************************
 
	Guy Shaked - 205717952 
	your name
	Main file - Tetris game
	
***************************************/
//#include <windows.h>

#include "Game.h"

using namespace std;

int main() {

	hideCursor();
	Game game;
	game.menuPage();
	gotoxy(WINNING_MASSAGE);
	cout << "Hope you enjoyed :), see you next time!" << endl << endl << endl << endl;

	//Game g;
	//g.init();
}



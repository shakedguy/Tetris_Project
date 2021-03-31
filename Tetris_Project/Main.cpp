/***************************************
 
	Guy Shaked - 205717952 
	your name
	Main file - Tetris game
	
***************************************/
#include <windows.h>
#include <iostream>
#include "Game.h"


using namespace std;


int main() {

	Game game;
	game.init();
	game.run();
	gotoxy(23, 23);
	cout << endl << endl;
}

/***************************************
 
	Guy Shaked - 205717952 
	your name
	Main file - Tetris game
	
***************************************/
#include <windows.h>
#include <iostream>
#include "Game.h"
#include "Point.h"
using namespace std;


int main() {

	Game game;
	game.init();
	////game.run();
	gotoxy(25, 25);
	cout << endl << endl;
}

/***************************************
 
	Guy Shaked - 205717952 
	your name
	Main file - Tetris game
	
***************************************/
#include <windows.h>
#include <iostream>
#include <time.h>
#include "Game.h"
#include "Point.h"
using namespace std;


int main() {

	srand((int)time(0));
	Game game;
	game.init();
	////game.run();
	gotoxy(23, 23);
	cout << endl << endl;

	
}

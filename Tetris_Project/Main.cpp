/***************************************
 
	Guy Shaked - 205717952 
	your name
	Main file - Tetris game
	
***************************************/
#include <windows.h>
#include <iostream>
#include <ctime>
#include "Game.h"
using namespace std;


int main() {

	srand(time(0));
	Game game;
	game.init();
	game.run();
	gotoxy(23, 23);
	cout << endl << endl;
	///*  guy shaked */


}

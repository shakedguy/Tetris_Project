/***************************************
 
	Guy Shaked - 205717952 
	your name
	Main file - Tetris game
	
***************************************/
#include <windows.h>
#include <iostream>

#include "Game.h"


using namespace std;


/************ To switch to color mode go to "Public const and structs.h" file ****************/
/************ and remove the Comment mark ( // ) from the #define ___COLORS___ **************/
int main() {

	Game game;
	game.menuPage();
	gotoxy(15, 5);
	cout << "Hope you enjoyed :), see you next time!" << endl << endl << endl;
}



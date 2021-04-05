/***************************************
 
	Guy Shaked - 205717952 
	your name
	Main file - Tetris game
	
***************************************/
#include <windows.h>
#include <iostream>
#include <list>

#include "Game.h"

#include "Menu.h"


using namespace std;



int main() {

	Game game;
	game.menuPage();
	gotoxy(15, 5);
	cout << "Hope you enjoyed :), see you next time!" << endl << endl;
	//list<char> lst;
	//for (int i = 0; i < 10; i++)
	//	lst.push_front('a' + i);
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << lst.front() << ' ';
	//	lst.pop_front();
	//}
}



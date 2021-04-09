/***************************************
	Header file for the consts and structs of all the project.
***************************************/
#ifndef _CONSTS_STRUCTS_H_
#define _CONSTS_STRUCTS_H_

#include <iostream>

using namespace std;


#define LEFT_BOARD_POS 40,4 //(x,y) location of player 1 board
#define LEFT_BOX_POS 20,15 //(x,y) location of player 1 box
#define LEFT_SCORE_POS 20,3 //(x,y) location of player 1 score
#define RIGHT_BOARD_POS 60,4 //(x,y) location of player 2 board
#define RIGHT_BOX_POS 80,15 //(x,y) location of player 2 box
#define RIGHT_SCORE_POS 80,3 //(x,y) location of player 2 score
#define LEFT_CURRENT_BLOCK 44,2
#define RIGHT_CURRENT_BLOCK 64,2
#define MENU_BOARD_POS 35,0
#define WINNING_MASSAGE 35,10
#define MENU_BLOCK_LENGTH 5
#define MENU_BLOCK_WIDTH 40
#define BOARD_LENGTH 18
#define BOARD_WIDTH 12
#define BOX_LENGTH 8
#define BOX_WIDTH 8
#define EMPTY_CELL ' '
#define PLAYER_ONE_KEYS "wsxad"
#define PLAYER_TWO_KEYS "ikmjl"
#define BLOCK_MATRIX 4
#define NEW_GAME_INPUT 1
#define RESUME_GAME_INPUT 2
#define SET_NAMES_INPUT 3
#define COLOR_MODE_INPUT 4
#define INSTRUCTIONS_AND_KEYS 8
#define EXIT_GAME_INPUT 9
#define POINTS_FOR_FULL_ROW 100
#define BOXES_IN_MENU 6
#define BLOCKS_IN_BOX 2
#define BLOCKS_IN_MENU 8
#define NUMBER_OF_KEYS 5
#define kEY_INDIVATORS_WIDTH 3
#define kEY_INDIVATORS_LENGTH 3

typedef unsigned int uint;
typedef unsigned short int ushort;
typedef short int sint;
typedef unsigned char uchar;


enum Boundaries
{
	WALL = 186, FLOOR = 205, UP_LEFT = 201, UP_RIGHT = 187, DOWN_LEFT = 200, DOWN_RIGHT = 188,
	RIGHT_CONNECTOR = 185, LEFT_CONNECTOR = 204
};
enum Moves { UP = 6, DOWN, LEFT, RIGHT };
enum Keys { COUNTER_CLOCKWISE, CLOCKWISE, DROP, MOVE_LEFT, MOVE_RIGHT, DEFAULT, ESC = 27 };
enum Shapes { SHAPE = 178, SHAPE_AFTER_FREEZE = 219 };

#endif
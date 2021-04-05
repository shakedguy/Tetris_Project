/***************************************
	Header file for the consts and structs of all the project. 
***************************************/
#ifndef _CONSTS_STRUCTS_H_
#define _CONSTS_STRUCTS_H_


#define ___COLORS___


#include <iostream>

using namespace std;

#define LEFT_BOARD_POS 15,0 //(x,y) location of player 1 board
#define LEFT_BOX_POS 0,13 //(x,y) location of player 1 box
#define LEFT_SCORE_POS 0,3 //(x,y) location of player 1 score
#define RIGHT_BOARD_POS 60,0 //(x,y) location of player 2 board
#define RIGHT_BOX_POS 105,13 //(x,y) location of player 2 box
#define RIGHT_SCORE_POS 103,3 //(x,y) location of player 2 score
#define LEFT_CURRENT_BLOCK 35,2
#define RIGHT_CURRENT_BLOCK 80,2
#define MENU_BOARD_POS 35,1
#define WINNING_MASSAGE 35,3
#define MENU_BLOCK_LENGTH 5
#define MENU_BLOCK_WIDTH 40
#define BOARD_LENGTH 25
#define BOARD_WIDTH 40
#define BOX_LENGTH 12
#define BOX_WIDTH 11
#define EMPTY_CELL ' '
#define PLAYER_ONE_KEYS "wzads"
#define PLAYER_TOW_KEYS "imjlk"
#define BLOCK_MATRIX 4
#define NEW_GAME_INPUT 1
#define RESUME_GAME_INPUT 2
#define KEYS_AND_INSTRUCTIONS 3
#define EXIT_GAME_INPUT 4
#define POINTS_FOR_FULL_ROW 100
#define BOXES_IN_MENU 4
#define BLOCKS_IN_BOX 2
#define BLOCKS_IN_MENU 12

enum Boundaries{ WALL = 186, FLOOR = 205, UP_LEFT = 201, UP_RIGHT = 187, DOWN_LEFT = 200, DOWN_RIGHT = 188 };
enum Moves { UP, DOWN, LEFT, RIGHT };
enum Buttons { CLOCKWISE, COUNTER_CLOCKWISE = 4, DROP = 5, ESC = 27 };
enum Shapes { SHAPE = 178, SHAPE_AFTER_FREEZE = 219 };



#endif
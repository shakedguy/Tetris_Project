/***************************************
	Header file for the consts and structs of all the project. 
***************************************/
#ifndef _CONSTS_STRUCTS_H_
#define _CONSTS_STRUCTS_H_

#include <iostream>

using namespace std;

#define LEFT_BOARD_POS 15,5 //(x,y) location of player 1 board
#define LEFT_BOX_POS 0,13 //(x,y) location of player 1 box
#define LEFT_SCORE_POS 0,3 //(x,y) location of player 1 score
#define RIGHT_BOARD_POS 60,5 //(x,y) location of player 2 board
#define RIGHT_BOX_POS 105,13 //(x,y) location of player 2 box
#define RIGHT_SCORE_POS 105,3 //(x,y) location of player 2 score
#define LEFT_CURRENT_BLOCK 35,4
#define RIGHT_CURRENT_BLOCK 80,4
#define BOARD_LENGTH 20
#define BOARD_WIDTH 40
#define BOX_LENGTH 12
#define BOX_WIDTH 11
#define SHAPE 219
#define EMPTY_CELL ' '
#define PLAYER_ONE_KEYS "wzad"
#define PLAYER_TOW_KEYS "imjl"
#define BLOCK_MATRIX 4

enum { WALL = 186, FLOOR = 205, UP_LEFT = 201, UP_RIGHT = 187, DOWN_LEFT = 200, DOWN_RIGHT = 188 };
enum { UP, DOWN, LEFT, RIGHT };



#endif
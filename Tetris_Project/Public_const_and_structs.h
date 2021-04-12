/***************************************
	Header file for the consts and structs of all the project.
***************************************/
#ifndef _CONSTS_STRUCTS_H_
#define _CONSTS_STRUCTS_H_

/* In this file all the const parameters of the project will be written,
 * so if we will want to change sizes, locations or characters of objects,
 * we can do it from here and will not have to change each file of the relevant class */

#include <iostream>
#include "io_utils.h"
#include <random>
#include <stdio.h>
#include <vector>
#include <map>
#include <array>
#include "Colors.h"
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::array;
using std::vector;
using std::string;
using std::map;


#define LEFT_BOARD_POS 40,4 //(x,y) location of player 1 board
#define LEFT_BOX_POS 20,15 //(x,y) location of player 1 box
#define LEFT_SCORE_POS 20,5 //(x,y) location of player 1 score
#define RIGHT_BOARD_POS 60,4 //(x,y) location of player 2 board
#define RIGHT_BOX_POS 80,15 //(x,y) location of player 2 box
#define RIGHT_SCORE_POS 80,5 //(x,y) location of player 2 score
#define LEFT_CURRENT_BLOCK 44,2
#define RIGHT_CURRENT_BLOCK 64,2
#define MENU_BOARD_POS 35,0
#define WINNING_MASSAGE 30,10
#define SPEED_MODE_BUTTON_POS 1,2 //(x,y) location of player 2 board
#define MENU_BLOCK_LENGTH 5
#define MENU_BLOCK_WIDTH 40
#define BOARD_LENGTH 19
#define BOARD_WIDTH 14
#define BOX_LENGTH 8
#define BOX_WIDTH 8
#define EMPTY_CELL ' '// Define the character of the empty cell in the board
#define PLAYER_ONE_KEYS "wsxad" // Const of game characters for player 1
#define PLAYER_TWO_KEYS "ikmjl" // Const of game characters for player 2
#define BLOCK_MATRIX 4
#define NEW_GAME_INPUT 1
#define RESUME_GAME_INPUT 2
#define SET_NAMES_INPUT 3
#define COLOR_MODE_INPUT 4
#define INSTRUCTIONS_AND_KEYS 8
#define EXIT_GAME_INPUT 9
#define POINTS_FOR_FULL_ROW 100 // Define how many points player gets for filling a line
#define BLOCKS_IN_BOX 2 // Define how many blocks are in a box
#define BLOCKS_IN_MENU 8
#define NUMBER_OF_KEYS 5 // Define how many keys is available to the player
#define kEY_INDIVATORS_WIDTH 3
#define kEY_INDIVATORS_LENGTH 3
#define TIE_GAME_CODE 2
#define GAME_SPEED 200 // Define the game's default speed
#define ACCELERATION 30 // Define the acceleration height in speed mode
#define GAME_BUTTONS 2 // Define how many modes buttons the game have
#define GAME_BUTTON_WIDTH 11
#define GAME_BUTTON_LENGTH 5
#define NUM_OF_PLAYERS 2 // Define the number of players in the game
#define BLOCKS_FOR_ACCELERATION 5 // Define how many freezing blocks in the board needed for acceleration
#define SCORE_FOR_ACCELERATION 20 // Define how many points is needed for acceleration

using ushort = unsigned short int;
using uint = unsigned int;
using sint = short int;
using uchar = unsigned char;

// Defining the shape fill characters as consts
enum Shapes { SHAPE = 178, SHAPE_AFTER_FREEZE = 219 };

// Define the numbers that represent steps as consts
enum Keys { COUNTER_CLOCKWISE, CLOCKWISE, DROP, MOVE_LEFT, MOVE_RIGHT, SPEED_MODE = 42, DEFAULT, ESC = 27 };

#endif

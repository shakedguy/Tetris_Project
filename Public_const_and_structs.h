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


#define EMPTY_CELL ' '// Define the character of the empty cell in the board


using ushort = unsigned short int;
using uint = unsigned int;
using sint = short int;
using uchar = unsigned char;


// Define the numbers that represent steps as consts
enum Keys { COUNTER_CLOCKWISE, CLOCKWISE, DROP, MOVE_LEFT, MOVE_RIGHT, DEFAULT, SPEED_MODE = 42, ESC = 27 };



#endif

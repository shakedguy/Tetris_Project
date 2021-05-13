/***************************************
	Header file for class "Game".
***************************************/
#ifndef _GAME_H_
#define _GAME_H_

#include "Public_const_and_structs.h"
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "Computer_Player.h"



class Game
{

	/********************************** Menu class *****************************************/
	/**************************************************************************************/
	class Menu
	{

		static constexpr char humanVShuman[] = "humanVScomputer";
		static constexpr char humanVScomputer[] = "humanVScomputer";
		static constexpr char computerVScomputer[] = "computerVScomputer";
		static constexpr size_t NUM_OF_BLOCKS = 8, MENU_BLOCK_LENGTH = 5,
			MENU_BOARD_WIDTH = 40, MENU_BOARD_LENGTH = 21, NUM_OF_OPTIONS = 4;
		enum objectsPositions
		{
			MENU_X = 15, MENU_Y = 0,
			LEFT_BLOCKS_DISTANCE = -8, RIGHT_BLOCKS_DISTANCE = 48, TEXT_Y = 2,
			INSTRUCTIONS = 2, RESUME_GAME_X, SET_NAMES_X, VERTICAL_BLOCKS_DISTANCE = 5,
			COLOR_MODE_ON = 5, COLOR_MODE_OF, NEW_GAME_X = 9, EXIT = 11,
		};
		static bool resumeGame;
		
		enum GameOptions {
			H_VS_H, H_VS_C, C_VS_C, PRINT_C_C, PRINT_H_C, PRINT_H_H = 6, BACK, BEST = 0, GOOD, NOVICE,
			PRINT_BEST = 8, PRINT_GOOD = 8, PRINT_NOVICE = 7
		};
		enum inputs {
			NEW_GAME = 1, RESUME_GAME, SET_NAMES, COLOR_MODE, INSTRUCTIONS_AND_KEYS = 8, EXIT_GAME
		};
		enum Constants { MAIN_MENU_PAGE, NEW_GAME_PAGE, LEVELS_PAGE, NUM_OF_PAGES };
		Coordinate pos;
		array<Board, NUM_OF_PAGES> menuPages;
		array<Block, NUM_OF_BLOCKS> blocks;

		friend class Game;

	private:
		void printOptions(const ushort& pageNumber)const;
		void printMainMenuOptions() const;
		void printNewGamePageOptions()const;
		void printLevelsPageOptions()const;
		void paintBoxes(const ushort& pageNumber) const;
		void drawBlocksInMenu() const;
		void drawPage(const ushort& pageNumber) const;
		void setMenuBlock();
		void pickColor(const size_t& row) const;
		void keyAndInstructions()const;
		void setMenuBoard();
		void setNewGameAndLevelsMenus();
		void inputErrorMassage()const;
		void newGamePage(Game& game)const;
		void levelsPage(Game& game, const string& option)const;


	public:
		Menu() : Menu({ 0, 0 }) {}
		Menu(const Coordinate& _pos);
		~Menu() = default;
		friend std::ostream& operator<<(std::ostream& out, const Menu& _menu) { _menu.drawPage(MAIN_MENU_PAGE); return out; }
		static void possibleResumeGame(const bool& possible) { Menu::resumeGame = possible; }
		ushort getOption()const { return _getch() - '0'; }
		void mainMenuPage(Game& game)const;
		void updateMenuBoard();
	};

	 /**********************************************************************************************/
     /********************************** End of Menu class *****************************************/

	static constexpr size_t NUM_OF_PLAYERS = 2, NUM_OF_BUTTONS = 2, HITS_LIMIT = 10,
		LEFT_BOARD = 30, RIGHT_BOARD = 50, BOARDS_Y = 0, LEFT_BOX = 18, RIGHT_BOX = 68, BOXES_Y = 11,
		WINNING_MASSAGE_X = 30, WINNING_MASSAGE_Y = 20, SPEED_X = 0, SPEED_Y = 0, GAME_BUTTON_LENGTH = 5;
	static constexpr char PLAYER_ONE_KEYS[] = "wsxad"; // Const of game characters for player 1
	static constexpr char PLAYER_TWO_KEYS[] = "ikmjl";// Const of game characters for player 2
	
	enum Constants {
		GAME_SPEED = 60, ACCELERATION = 10, GAME_BUTTON_WIDTH = 11, TIE_GAME_CODE = 2
	};

		static bool colorsMode;
		static bool speedMode;
		size_t accNum = 1;
		array<Board, NUM_OF_BUTTONS> buttons;
		size_t gameSpeed;
		Menu menu;
		array<Player*, NUM_OF_PLAYERS>players;
		array<HumanPlayer, NUM_OF_PLAYERS>humanPlayers;
		array<ComputerPlayer, NUM_OF_PLAYERS>computerPlayers;
		ushort gameNumber = 0;
	


private:
		uchar avoidMultipleHits()const;
		void move() { players[0]->move(); players[1]->move(); }
		void printScores() const { players[0]->printScore(); players[1]->printScore(); }
		void clearGame() { players[0]->clearGame();	players[1]->clearGame(); }
		bool isSomeoneLose();
		void avoidMultipleMoves(uchar& key, const uchar& temp1, const uchar& temp2);
		void setNames();
		static void changeColorsMode();
		void winningMassage(const ushort& flag) const;
		void checkSpeedStatus();
		void setGameButtons();
		void printButtonsInfo();
		void checkGameModes(const uchar& key);
		void directions(const uchar& key);
		void returnLastSpeed();
		void resetCurrentBlocksPos();
		void resetIndicators();
		bool initializePlayers(const string& option);

public:
	Game();
	~Game(); 
	static void changeSpeedMode();
	void drawButtons();
	void acceleration() { gameSpeed -= ACCELERATION; accNum++; }
	void startGame() { menu.mainMenuPage(*this); }
	void init(const string& option);
	void run();
};




#endif

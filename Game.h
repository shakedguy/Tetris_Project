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
	class Menu
	{
		enum objectsPositions
		{
			MENU_X = 15, MENU_Y = 0,
			LEFT_BLOCKS_DISTANCE = -8, RIGHT_BLOCKS_DISTANCE = 48, TEXT_Y = 2,
			INSTRUCTIONS = 2, RESUME_GAME_X, SET_NAMES_X, VERTICAL_BLOCKS_DISTANCE = 5,
			COLOR_MODE_ON = 5, COLOR_MODE_OF, NEW_GAME_X = 9, EXIT = 11,
		};
		static bool resumeGame;
		enum GameOptions { H_VS_H, H_VS_C, C_VS_C, PRINT_C_C, PRINT_H_C, PRINT_H_H = 6, BACK  };
		enum inputs {
			NEW_GAME = 1, RESUME_GAME, SET_NAMES, COLOR_MODE, INSTRUCTIONS_AND_KEYS = 8, EXIT_GAME
		};
		enum Constants { NUM_OF_BLOCKS = 8, MENU_BLOCK_LENGTH = 5, MENU_BOARD_WIDTH = 40, MENU_BOARD_LENGTH = 21, NUM_OF_OPTIONS = 4 };
		Point pos;
		Board menu;
		Board newGameMenu;
		array<Block, NUM_OF_BLOCKS> blocks;
		friend class Game;

	private:
		void printMenuOptions() const;
		void printMenuColor() const;
		void drawBlocksInMenu() const;
		void drawMenu() const;
		void drawNewGameMenu() const;
		void setMenuBlock();
		void pickColor(const int& row) const;
		void keyAndInstructions();
		void setMenuBoard();
		void setNewGameMenuBoard();
		void inputErrorMassage();
		void newGameOptions(Game& game);
		void printNewGameMenuOptions()const;

	public:
		Menu() : Menu({ 0, 0 }) {}
		Menu(const Point& _pos);
		~Menu() = default;
		friend std::ostream& operator<<(std::ostream& out, const Menu& _menu) { _menu.drawMenu(); return out; }
		static void possibleResumeGame(const bool& possible);
		ushort getOption() { return _getch() - '0'; }
		Point getLastBoxPos()const;
		void menuPage(Game& game);
		void updateMenuBoard();
	};

/********************************** End of Menu class *****************************************/
	enum Constants {
		NUM_OF_PLAYERS = 2, HITS_LIMIT = 10, GAME_SPEED = 200, ACCELERATION = 30,
		NUM_OF_BUTTONS = 2, GAME_BUTTON_WIDTH = 11, GAME_BUTTON_LENGTH = 5, TIE_GAME_CODE = 2
	};
	enum objectsPositions {
		LEFT_BOARD = 30, RIGHT_BOARD = 50, BOARDS_Y = 0,
		LEFT_BOX = 18, RIGHT_BOX = 68, BOXES_Y = 11, SPEED_X = 0, SPEED_Y = 0
	};
	static bool colorsMode;
	static bool speedMode;
	ushort accNum = 1;
	array<Board, NUM_OF_BUTTONS> buttons;
	ushort gameSpeed = GAME_SPEED;
	Menu menu;
	array<Player*, NUM_OF_PLAYERS>players;
	array<HumanPlayer, NUM_OF_PLAYERS>humanPlayers;
	array<ComputerPlayer, NUM_OF_PLAYERS>computerPlayers;
	ushort gameNumber = 0;

	friend class Menu;

private:
	uchar avoidMultipleHits();
	void move() { players[0]->move(); players[1]->move(); }
	void drawBoards() const { players[0]->drawBoard();	players[1]->drawBoard(); }
	void printScores() const { players[0]->printScore(); players[1]->printScore(); }
	void clearGame() { players[0]->clearGame();	players[1]->clearGame(); }
	bool isSomeoneLose();
	bool resumeGame();
	void avoidMultipleMoves(uchar& key, const uchar& temp1, const uchar& temp2);
	void setNames() { players[0]->setName();	players[1]->setName(); }
	void changeColorsMode();
	void winningMassage(const ushort& flag) const;
	void checkSpeedStatus();
	void setGameButtons();
	void printButtonsInfo();
	void checkGameModes(const uchar& key);
	void directions(const uchar& key);
	void returnLastSpeed();
	void resetCurrentBlocksPos();
	void resetIndicators();
	bool initializePlayers(const ushort& option);

public:
	Game();
	~Game() = default;
	static void changeSpeedMode();
	void drawButtons();
	void acceleration() { gameSpeed -= ACCELERATION; accNum++; }
	void startGame() { menu.menuPage(*this); }
	void init(const ushort& option);
	void run();

	
};

#endif

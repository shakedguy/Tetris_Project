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
#include "MyException.h"
#include "Files_Handler.h"
#include "FilePlayer.h"


class Game
{

	/********************************** Menu class *****************************************/
	/**************************************************************************************/
	class Menu
	{

		static bool resumeGame;
		static constexpr char HUMAN_VS_HUMAN[] = "h vs h";
		static constexpr char HUMAN_VS_COMPUTER[] = "h vs c";
		static constexpr char COMPUTER_VS_COMPUTER[] = "c vs c";
		static constexpr size_t NUM_OF_BLOCKS = 8, MENU_BLOCK_LENGTH = 5,
			MENU_BOARD_WIDTH = 40, MENU_BOARD_LENGTH = 21, NUM_OF_OPTIONS = 4;

		enum Levels { BEST, GOOD, NOVICE, };
		enum GameOptions { H_VS_H, H_VS_C, C_VS_C, };
		enum PageNumbers { MAIN_MENU_PAGE, NEW_GAME_PAGE, LEVELS_PAGE, NUM_OF_PAGES };
		enum Inputs { NEW_GAME = 1, RESUME_GAME, SET_NAMES, COLOR_MODE, INSTRUCTIONS_AND_KEYS = 8, EXIT_GAME };
		enum objectsPositions {
			MENU_X = 15, MENU_Y = 0, LEFT_BLOCKS_DISTANCE = -8, TEXT_Y = 2,
			RIGHT_BLOCKS_DISTANCE = 48, VERTICAL_BLOCKS_DISTANCE = 5
		};
		enum Prints {
			INSTRUCTIONS = 2, RESUME_GAME_X,
			PRINT_C_C = 3, PRINT_H_C, SET_NAMES_X = 4, BACK = 4, COLOR_MODE_ON, COLOR_MODE_OF,
			PRINT_H_H = 6, PRINT_NOVICE,
			PRINT_BEST, PRINT_GOOD = 8, NEW_GAME_X, EXIT = 11
		};

		Point pos;
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
		Menu(const Point& _pos);
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
		LEFT_BOARD = 30, RIGHT_BOARD = 50, BOARDS_Y = 1, LEFT_BOX = 18, RIGHT_BOX = 68, BOXES_Y = 11,
		WINNING_MASSAGE_X = 20, WINNING_MASSAGE_Y = 5, SPEED_X = 0, SPEED_Y = 0,
		GAME_BUTTON_LENGTH = 5, MAX_SPEED = 15;
	static constexpr char PLAYER_ONE_KEYS[] = "wsxad", PLAYER_TWO_KEYS[] = "ikmjl";
	static constexpr char SAVE_MODE[] = "-save", LOAD_MODE[] = "-load", SILENT_MODE[] = "-silent";
	static constexpr size_t GAME_SPEED = 60, ACCELERATION = 10;
	
	
	enum Constants { GAME_BUTTON_WIDTH = 11, TIE_GAME = 0, INCOMPLETED = -1 };
	enum Game_Modes { SIMPLE, SAVE, LOAD, SILENT };
	enum class File_Types { BLOCKS_FILES, MOVES_FILES, RESULT_FILE, NUM_OF_FILE_TYPES };

	static ushort gameMode;
	static bool colorsMode;
	static bool speedMode;
	static size_t gameSpeed;
	static size_t accNum;
	array<Board, NUM_OF_BUTTONS> buttons;
		
		Menu menu;
		array<Player*, NUM_OF_PLAYERS>players;
		ushort gameNumber = 0;
		size_t cycle = 0;
		Result_File result;
	
		
	


private:
		uchar avoidMultipleHits()const;
		void move();
		void enableUserInput(uchar& key, uchar& prev, uchar& prevPrev);
		void printScores() const { players[0]->printScore(); players[1]->printScore(); }
		void clearGame();
		bool isSomeoneLose();
		bool tieGame();
		bool playerOneWon();
		bool playerTowWon();
		bool paused();
		void saveNoWinnerGame(const short& gameResult);
		void saveGame(const short& winner);
		void avoidMultipleMoves(uchar& key, const uchar& temp1, const uchar& temp2);
		void setNames();
		static void changeColorsMode();
		void winningMassage(const int& winner);
		void checkSpeedStatus();
		void setGameButtons();
		void printButtonsInfo();
		void checkGameModes(const uchar& key);
		void directions(uchar& key);
		static void returnLastSpeed();
		void resetCurrentBlocksPos();
		void resetIndicators();
		void initializePlayers(const string& option) noexcept(false);
		void openGameMode(int argc, char* argv[])noexcept(false);
		static void changeGameMode(const ushort& mode) { Game::gameMode = mode; Player::changeGameMode(mode); }
		bool endGame(const uchar& key);
		void continuePlaying();
		bool completedGameResultCheck(const ushort& playerNum, const Point& highestPoint);
		bool inCompletedGameResultcheck(const ushort& gameResult);
		void allocateHumanPlayers() noexcept(false);
		void allocateComputerPlayers() noexcept(false);
		void allocateFilePlayers() noexcept(false);
		void allocateHuman_VS_Computer() noexcept(false);
		void isEndOfFiles()const;
		void deletePlayers() { delete players[0]; delete players[1]; }

public:

	Game();
	~Game();
	static void changeSpeedMode();
	void resumeGame();
	void drawButtons();
	static inline void acceleration();
	void startGame(int argc, char* argv[])noexcept(false);
	void init(const string& option)noexcept(false);
	void run();
};




#endif

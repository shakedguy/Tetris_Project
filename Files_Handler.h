#pragma once
#include "Public_const_and_structs.h"
#include "Point.h"
#include "MyException.h"

using std::fstream;

class Files_Handler
{
protected:

	static constexpr char GAME_1_FOLDER[] = "game1";
	static constexpr char GAME_2_FOLDER[] = "game2";
	static constexpr char GAME_3_FOLDER[] = "game3";
	string path1, path2, path3;
	fstream file;

public:
	Files_Handler() {}
	virtual ~Files_Handler() {}
	static constexpr char read = 'r';
	static constexpr char write = 'w';
	void pushFiles();
	string makePath(const string& folder, const string& fileName);
	void copyFile(const string& data, const string& des)const;
	bool openToRead(fstream& file, const string& path)const;
	bool openToWrite(fstream& file, const string& path)const;
	void openFilesToWrite();
	void openFilesToRead();
	virtual void saveData(const short& blockNum, const size_t& cycle, const short& dir) = 0;
	virtual void print() = 0;
	virtual void readData() = 0;
	virtual short getData(const size_t& cycle) = 0;
	virtual void clearGame() { std::remove(path1.c_str()); }
	virtual bool isEmpty()const = 0;
	virtual short getFirst()const = 0;
};

class Blocks_Files : virtual public Files_Handler
{

	static constexpr char A_BLOCKS[] = "/a.blocks.bin", B_BLOCKS[] = "/b.blocks.bin";
	list<short> blocks;

	
private:
	void makeLeftPathes();
	void makeRightPathes();
	

public:
	Blocks_Files(const ushort& playerNum, const char& mode);
	~Blocks_Files();
	void print()override;
	void saveData(const short& blockNum, const size_t& cycle, const short& dir)override
		{ blocks.push_back(blockNum); }
	void readData()override;
	short getData(const size_t& cycle)override;
	void clearGame()override { blocks.clear(); Files_Handler::clearGame(); }
	bool isEmpty()const override { return blocks.empty(); }
	short getFirst()const;
};

class Moves_Files : virtual public Files_Handler
{
	static constexpr char A_MOVES[] = "/a.moves.bin", B_MOVES[] = "/b.moves.bin";
	list<pair<size_t, short>> moves;

private:
	void makeLeftPathes();
	void makeRightPathes();
	

public:
	Moves_Files(const ushort& playerNum, const char& mode);
	~Moves_Files();
	void print()override;
	void saveData(const short& blockNum, const size_t& cycle, const short& dir)override
	{	moves.push_back(pair<long long, short>{ cycle, dir });	}
	void readData()override;
	short getData(const size_t& cycle)override;
	void clearGame()override { moves.clear(); Files_Handler::clearGame(); }
	bool isEmpty()const override { return moves.empty(); }
	short getFirst()const;

	
};

class Result_File : virtual public Files_Handler
{
	static constexpr char RESULT[] = "/expected.result.bin";

public:
	Result_File();
	~Result_File();
	void print()override {}
	void printOnePlayerResult(const short& playerNum, const size_t& cycle, const Point& highestPoint);
	void saveData(const short& blockNum, const size_t& cycle, const short& dir)override { return; }
	void readOnePlayerResult(short& playerNum, size_t& cycle, Point& highestPoint);
	void readTowPlayersResult(short& result, size_t& cycle, Point& first,
		Point& second);
	void printTowPlayerResult(const short& result, const size_t& cycle,
		const Point& first,const Point& second);
	void readData()override {}
	short getData(const size_t& cycle)override { return 0; }
	void clearGame()override { Files_Handler::clearGame(); }
	bool isEmpty()const override { return true; }
	short getFirst()const { return 0; }

};


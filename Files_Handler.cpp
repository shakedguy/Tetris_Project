#include "Files_Handler.h"
#include <string.h>

Blocks_Files::Blocks_Files(const ushort& playerNum, const char& mode)
{
	if (playerNum == 1)
		makeLeftPathes();
	else
		makeRightPathes();
	if (read == mode)
		readData();
}

Moves_Files::Moves_Files(const ushort& playerNum, const char& mode)
{
	if (playerNum == 1)
		makeLeftPathes();
	else
		makeRightPathes();
	if (read == mode)
		readData();
}

Result_File::Result_File()
{
	path1 = makePath(GAME_1_FOLDER, RESULT);
	path2 = makePath(GAME_2_FOLDER, RESULT);
	path3 = makePath(GAME_3_FOLDER, RESULT);
}

void Blocks_Files::makeLeftPathes()
{
	path1 = makePath(GAME_1_FOLDER, A_BLOCKS);
	path2 = makePath(GAME_2_FOLDER, A_BLOCKS);
	path3 = makePath(GAME_3_FOLDER, A_BLOCKS);
}


void Blocks_Files::makeRightPathes()
{
	path1 = makePath(GAME_1_FOLDER, B_BLOCKS);
	path2 = makePath(GAME_2_FOLDER, B_BLOCKS);
	path3 = makePath(GAME_3_FOLDER, B_BLOCKS);
}

void Moves_Files::makeLeftPathes()
{
	path1 = makePath(GAME_1_FOLDER, A_MOVES);
	path2 = makePath(GAME_2_FOLDER, A_MOVES);
	path3 = makePath(GAME_3_FOLDER, A_MOVES);
}


void Moves_Files::makeRightPathes()
{
	path1 = makePath(GAME_1_FOLDER, B_MOVES);
	path2 = makePath(GAME_2_FOLDER, B_MOVES);
	path3 = makePath(GAME_3_FOLDER, B_MOVES);
}


Blocks_Files::~Blocks_Files()
{
	if(file.is_open())
		file.close();
}

void Blocks_Files::print()
{
	
	if (!blocks.empty())
	{
		short x;
		openFilesToWrite();
		for (short& i : blocks)
		{
			x = i;
			file.write(reinterpret_cast<char*>(&x), sizeof(x));
		}
	}
	else
		file << -1;
	file.close();
}


Moves_Files::~Moves_Files()
{
	if (file.is_open())
		file.close();
}

void Moves_Files::print()
{
	if (!moves.empty())
	{
		openFilesToWrite();
		size_t cycle;
		short move;
		for (pair<size_t, short> i : moves)
		{
			cycle = i.first;
			move = i.second;
			file.write(reinterpret_cast<char*>(&cycle), sizeof(cycle));
			file.write(reinterpret_cast<char*>(&move), sizeof(move));
		}
	}
	else
		file << -1;
	file.close();
}

Result_File::~Result_File()
{
	if (file.is_open())
		file.close();
}

string Files_Handler::makePath(const string& folder, const string& fileName)
{
	string str;
	str += folder;
	str += fileName;
	return str;
}

bool Files_Handler::openToRead(fstream& file, const string& path) const
{
	file.open(path, std::ios::in | std::ios::binary);
	return file.is_open();
}

bool Files_Handler::openToWrite(fstream& file, const string& path) const
{
	file.open(path, std::ios::out | std::ios::binary);
	return file.is_open();
}

void Files_Handler::openFilesToRead()
{

	if (!openToRead(file, path3) || file.eof())
	{
		file.close();
		if (!openToRead(file, path2) || file.eof())
		{
			file.close();
			openToRead(file, path1);
		}

	}
	if (!file.is_open())
		throw OpenFileException();

}

void Files_Handler::copyFile(const string& data, const string& des)const
{
	fstream fin;
	if (openToRead(fin,data))
	{
		fstream fout;
		if (!openToWrite(fout, des))
			throw OpenFileException();

		fout << fin.rdbuf();
		fin.close();
		fout.close();
	}
}

void Files_Handler::openFilesToWrite()
{
	if (openToRead(file, path1) && !file.eof())
	{
		file.close();
		pushFiles();
	}
	else
		file.close();
	if (!openToWrite(file, path1))
		throw OpenFileException();
}

void Files_Handler::pushFiles()
{
	copyFile(path2, path3);
	copyFile(path1, path2);
}

void Result_File::printOnePlayerResult(const short& playerNum, const size_t& cycle,
	const Point& highestPoint)
{
	openFilesToWrite();
	const int x = highestPoint.getX(), y = highestPoint.getY();
	file.write(reinterpret_cast<const char*>(&playerNum), sizeof(playerNum));
	file.write(reinterpret_cast<const char*>(&cycle), sizeof(cycle));
	file.write(reinterpret_cast<const char*>(&x), sizeof(x));
	file.write(reinterpret_cast<const char*>(&y), sizeof(y));
	file.close();
}

void Result_File::readOnePlayerResult(short& playerNum, size_t& cycle, Point& highestPoint)
{
	openFilesToRead();
	int x, y;
	file.read(reinterpret_cast<char*>(&playerNum), sizeof(playerNum));
	file.read(reinterpret_cast<char*>(&cycle), sizeof(cycle));
	file.read(reinterpret_cast<char*>(&x), sizeof(x));
	file.read(reinterpret_cast<char*>(&y), sizeof(y));
	highestPoint.setXY(x, y);
	file.close();
}

void Result_File::readTowPlayersResult(short& result, size_t& cycle, Point& first,
	Point& second)
{
	if (!file.is_open())
		openFilesToRead();
	int x, y;
	file.read(reinterpret_cast<char*>(&result), sizeof(result));
	file.read(reinterpret_cast<char*>(&cycle), sizeof(cycle));
	file.read(reinterpret_cast<char*>(&x), sizeof(x));
	file.read(reinterpret_cast<char*>(&y), sizeof(y));
	first.setXY(x, y);
	int k, z;
	file.read(reinterpret_cast<char*>(&k), sizeof(x));
	file.read(reinterpret_cast<char*>(&z), sizeof(y));
	second.setXY(k, z);
}

void Result_File::printTowPlayerResult(const short& result, const size_t& cycle,
	const Point& first, const Point& second)
{
	openFilesToWrite();
	int x = first.getX(), y = first.getY();
	file.write(reinterpret_cast<const char*>(&result), sizeof(result));
	file.write(reinterpret_cast<const char*>(&cycle), sizeof(cycle));
	file.write(reinterpret_cast<const char*>(&x), sizeof(x));
	file.write(reinterpret_cast<const char*>(&y), sizeof(y));
	int k = second.getX();
	int z = second.getY();
	file.write(reinterpret_cast<const char*>(&k), sizeof(x));
	file.write(reinterpret_cast<const char*>(&z), sizeof(y));
	file.close();
}



void Blocks_Files::readData()
{
	openFilesToRead();
	short blockNum;

	while(!file.eof())
	{
		file.read(reinterpret_cast<char*>(&blockNum), sizeof(blockNum));
		blocks.push_back(blockNum);
		auto pos = file.tellg();
		if (char c = file.get() == EOF)
			break;
		file.seekg(pos, std::ios::beg);

		file.seekg(pos, std::ios::beg);
	}
	file.close();
}

short Blocks_Files::getData(const size_t& cycle)
{
	if (blocks.empty())
		return -1;
	short temp = blocks.front();
	blocks.pop_front();
	return temp;
}

short Moves_Files::getData(const size_t& cycle)
{
	if (moves.empty())
		return -1;
	if (moves.front().first != cycle)
		return static_cast<short>(DEFAULT);
		
	const short temp = moves.front().second;
	moves.pop_front();
	return temp;
}

void Moves_Files::readData()
{
	openFilesToRead();
	long long cycle;
	short move;
	string s = makePath(GAME_1_FOLDER, A_MOVES);
	while (!file.eof())
	{
		file.read(reinterpret_cast<char*>(&cycle), sizeof(cycle));
		file.read(reinterpret_cast<char*>(&move), sizeof(move));
		moves.push_back({ cycle,move });
		auto pos = file.tellg();
		if (char c = file.get() == EOF)
			break;		
		file.seekg(pos, std::ios::beg);
	}
	file.close();
}

short Blocks_Files::getFirst() const
{
	if (blocks.empty())
		return -1;
	return blocks.front();
}

short Moves_Files::getFirst() const
{
	if (moves.empty())
		return -1;
	return moves.front().first;
}








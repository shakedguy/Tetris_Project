#include "Files_Handler.h"



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
	openFilesToWrite();
	for (ushort& i : blocks)
		file.write(reinterpret_cast<char*>(&i), alignof(ushort));
	file.close();
}


Moves_Files::~Moves_Files()
{
	if (file.is_open())
		file.close();
}

void Moves_Files::print()
{
	openFilesToWrite();
	for (pair<size_t, ushort>& i : moves)
	{
		file.write(reinterpret_cast<char*>(&i.first), alignof(size_t));
		file.write(reinterpret_cast<char*>(&i.second), alignof(ushort));
	}
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
//
//void Moves_Files::openFilesToRead()
//{
//	openToRead(file, path1);
//	if (!file.is_open() || file.eof())
//	{
//		file.close();
//		openToRead(file, path2);
//		if (!file.is_open() || file.eof())
//		{
//			file.close();
//			openToRead(file, path3);
//		}
//	}
//	if (!file.is_open())
//		throw OpenFileException();
//}
//
//void Result_File::openFilesToRead()
//{
//	openToRead(file, path1);
//	if (!file.is_open() || file.eof())
//	{
//		file.close();
//		openToRead(file, path2);
//		if (!file.is_open() || file.eof())
//		{
//			file.close();
//			openToRead(file, path3);
//		}
//	}
//	if (!file.is_open())
//		throw OpenFileException();
//}
//
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

void Result_File::printResult(const short& playerNum, const size_t& cycle, const Point& highestPoint)
{
	openFilesToWrite();
	file.write(reinterpret_cast<const char*>(&playerNum), alignof(short));
	file.write(reinterpret_cast<const char*>(&cycle), alignof(size_t));
	file.write(reinterpret_cast<const char*>(&highestPoint.getX()), alignof(int));
	file.write(reinterpret_cast<const char*>(&highestPoint.getY()), alignof(int));
	file.close();
}

void Result_File::readResult(short& playerNum, size_t& cycle, Point& highestPoint)
{
	openFilesToRead();
	int x, y;
	file.read(reinterpret_cast<char*>(&playerNum), alignof(short));
	file.read(reinterpret_cast<char*>(&cycle), alignof(size_t));
	file.read(reinterpret_cast<char*>(&x), alignof(int));
	file.read(reinterpret_cast<char*>(&y), alignof(int));
	highestPoint.setXY(x, y);
	file.close();
}


void Blocks_Files::readData()
{
	openFilesToRead();
	short blockNum;
	while(!file.eof())
	{
		file.read(reinterpret_cast<char*>(&blockNum), alignof(short));
		blocks.push_back(blockNum);
		auto pos = file.tellg();
		if (char c = file.get() == EOF)
			break;
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
		return DEFAULT;
	short temp = moves.front().second;
	moves.pop_front();
	return temp;
}

void Moves_Files::readData()
{
	openFilesToRead();
	size_t cycle;
	short move;
	while (!file.eof())
	{
		file.read(reinterpret_cast<char*>(&cycle), alignof(size_t));
		file.read(reinterpret_cast<char*>(&move), alignof(short));
		moves.push_back({ cycle,move });
		auto pos = file.tellg();
		if (char c = file.get() == EOF)
			break;
		file.seekg(pos, std::ios::beg);
	}
	file.close();
}

//void Blocks_Files::getBlocks(const ushort& playerNum, list<ushort>& blocks)
//{
//	if (playerNum == 1)
//		return getBlocks(lFile, blocks);
//	else
//		return getBlocks(rFile, blocks);
//}
//
////void Blocks_Files::getBlocks(fstream& file, list<ushort>& blocks)
////{
////	ushort x;
////	while (!file.eof())
////	{
////		file.read(reinterpret_cast<char*>(&x), alignof(ushort));
////		blocks.push_back(x);
////	}
////	file.close();
////}
//
////void Moves_Files::getMoves(const ushort& playerNum, list<pair<size_t, ushort>>& moves)
////{
////	if (playerNum == 1)
////		return getMoves(lFile, moves);
////	else
////		return getMoves(rFile, moves);
////}
//
////void Moves_Files::getMoves(fstream& file, list<pair<size_t, ushort>>& moves)
////{
////	size_t x;
////	ushort y;
////	while(!file.eof())
////	{
////		file.read(reinterpret_cast<char*>(&x), alignof(size_t));
////		file.read(reinterpret_cast<char*>(&y), alignof(ushort));
////		moves.push_back({ x,y });
////	}
////	file.close();
////}








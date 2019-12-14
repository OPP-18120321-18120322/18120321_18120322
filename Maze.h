#pragma once
#include "Brick.h"
#include <sstream>
#include <fstream>
//#define FOLDER_MAZE "Maze/"
class Maze
{
public:
	//

	static const int MARGIN = 30;

	static const int NUMBER_COLUMN = 22;
	static const int NUMBER_ROW = 10;
private:
	//Create value
	int _map[NUMBER_ROW][NUMBER_COLUMN];
	//Show map
	vector<Brick> _bricks[NUMBER_ROW];
public:
	vector<Brick>& MazeBrick(int row) { return _bricks[row]; }
	Maze();
	void ReadFileMaze(string filename);
	void SetMap(SDL_Renderer* renderer, string fileimg, int num);
	void ShowMap();
};


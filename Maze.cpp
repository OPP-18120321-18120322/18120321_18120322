#include "Maze.h"

Maze::Maze() {
	for (int i = 0; i < NUMBER_ROW; i++) {
		for (int j = 0; j < NUMBER_COLUMN; j++) {
			_map[i][j] = 0;
		}
	}
}

void Maze::SetMap(SDL_Renderer* renderer,string fileimg, int num) {
	int i, j;
	string filename;
	string type;
	filename = "Maze/maze" + to_string(num) + ".txt";
	this->ReadFileMaze(filename);

	for (i = 0; i < NUMBER_ROW; i++) {

		for (j = 0; j < NUMBER_COLUMN; j++)
		{

			_bricks[i].push_back(Brick(renderer, fileimg, 1280 / 5 * 4 - Brick::BRICK_WIDTH * i, Brick::BRICK_LENGTH * j + MARGIN));

			if (_map[i][j] == 1)
			{
				_bricks[i][j].SetExist(1);
			}
			else if(_map[i][j] == 0)
			{
				_bricks[i][j].SetExist(0);
			}
		}
		//cout << endl;
	}

}

void Maze::ShowMap()
{
	for (int i = 0; i < NUMBER_ROW; i++)
	{
		for (auto brick : _bricks[i]) brick.Show();
		
	}
}
void Maze::WriteData(string filename)
{
	fstream file(filename, ios::out);
	for (int i = 0; i < NUMBER_ROW; i++) {
		for (int j = 0; j < NUMBER_COLUMN; j++) {
			file<< _bricks[i][j].IsExist()<<" ";
		}
		file << endl;
	}
	file.close();
}
void Maze::ReadFileMaze(string filename) {
	ifstream file_in(filename);

	if (file_in.fail()) {
		cout << "Khong the mo file" << endl;
		return;
	}

	for (int i = 0; i < NUMBER_ROW; i++) {
		for (int j = 0; j < NUMBER_COLUMN; j++) {
			file_in >>_map[i][j];
		}
	}

	file_in.close();
}
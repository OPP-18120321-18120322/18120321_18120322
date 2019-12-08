#include "Maze.h"

Maze::Maze() {
	for (int i = 0; i < NUMBER_ROW; i++) {
		for (int j = 0; j < NUMBER_COLUMN; j++) {
			_map[i][j] = 0;
		}
	}
}

void Maze::SetMap(SDL_Renderer* renderer, int num) {
	int i, j;
	string filename;
	string type;
	filename = "Maze/maze" + to_string(num) + ".txt";
	this->ReadFileMaze(filename);

	for (i = 0; i < NUMBER_ROW; i++) {

		for (j = 0; j < NUMBER_COLUMN; j++)
		{
			_bricks[i].push_back(Brick(renderer, 1280 / 4 * 3 - Brick::BRICK_WIDTH * i, 40 + Brick::BRICK_LENGTH * j));
			//cout << _map[i][j] << " ";
			if (_map[i][j] == 1)
			{
				_bricks[i][j].SetExist(1);
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
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "BaseObject.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
struct Info {
	string name;
	string score;
};

class Highscores
{
public:
	static const int DEFAULT_WIGHT = 300;
	static const int DEFAULT_HEIGHT = 60;
	static const int POS_RANK_X = 484;
	static const int POS_RANK_Y = 0;
	static const int POS_Y = 95;
private:
	vector<Object> _ranks;
	vector<Info> _players;
	vector<SDL_Rect> _position;

	SDL_Renderer* _render;
public:
	Highscores(SDL_Renderer*& renderer);
public:
	Info ReadInfo(string info);
	void ReadFile(string name_file);
	void ShowHighscores();
};


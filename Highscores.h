#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "BaseObject.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "SDL_TextView.h"

using namespace std;
struct Info 
{
	string name;
	string score;
};

class Highscores
{
public:
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;
private:
	Object _ranks;
	vector<Info> _players;

	SDL_Renderer* _render;
public:
	Highscores(SDL_Renderer*& renderer);
public:
	Info ReadInfo(string info);
	void ReadFile(string name_file);
	void WriteFile(Info data, string name_file);
	void ShowHighscores();
};


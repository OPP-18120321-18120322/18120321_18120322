#pragma once

#define SDL_MAIN_HANDLED

#include"Player.h"
#include"Ball.h"
#include <vector>
#include"BaseObject.h"
#include "SDL_TextView.h"
#include"Maze.h"

#include <time.h>
#include <SDL_timer.h>
#include"SDL_mixer.h"
#include "Time.h"

using namespace std;
class BrickBall
{
	
public:
	static const int DEFAULT_WIDTH = 1280;
	static const int DEFAULT_HEIGHT = 720;
	static const int DEFAULT_FPS = 60;

	static const int BORDER_LEFT = 240;// Bảng ben trái
	static const int MARGIN = 30;//Cách lề
	
private:
	Player _player;
	Ball _ball;
	vector<Object> _interfaces;
	vector<Object> img_hearts;
	Object avatar;
	Maze _maze;

	//SDL Framework
	SDL_Window* _window;
	SDL_Renderer* _render;

	Mix_Music* music = NULL;
	Mix_Chunk* chunk = NULL;

	int heart;
	bool is_playing;
	bool is_quit;
	int _score;
	int _width;
	int _height;

	int num;
	bool start;
public:
	void InitData();
	bool LoadData();
	void RestoreData();
	BrickBall();
	BrickBall(SDL_Window*& window, SDL_Renderer*& renderer, int, int);
	~BrickBall();
	void SetBrickBall(SDL_Window*& window, SDL_Renderer*& renderer,int ,int);
public:
	void ShowImg();
	void SaveGame();
	void PauseGame();
	void HandleWinLose();
	void ShowMenu();
	void HandleCollideBrick();
	void PlayGame();
};


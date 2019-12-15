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
	
	Maze _maze;

	//SDL Framework
	SDL_Window* _window;
	SDL_Renderer* _render;

	
	int heart;
	bool is_playing;
	bool is_quit;
	int _score;
	int _width;
	int _height;

	int _time_start;
	int _time_countdown;
public:
	void StartCountdown();
	int GetTime();
	void StopCountdown();
	void ShowTime();
public:
	void InitData();
	void RestoreData();
	BrickBall();
	BrickBall(SDL_Window*& window, SDL_Renderer*& renderer, int, int);
	~BrickBall();
	void SetBrickBall(SDL_Window*& window, SDL_Renderer*& renderer,int ,int);
public:
	void PauseGame();
	void HandleWinLose();
	int ShowMenu();
	void HandleCollideBrick();
	void PlayGame();
};


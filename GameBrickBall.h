#pragma once

#define SDL_MAIN_HANDLED
#include"Player.h"
#include"Ball.h"
#include <vector>
#include"BaseObject.h"
#include "SDL_TextView.h"

#define SDL_MAIN_HANDLED

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

	//SDL Framework
	SDL_Window* _window;
	SDL_Renderer* _render;

	int _width;
	int _height;
public:
	void Init();
	BrickBall();
	BrickBall(SDL_Window*& window, SDL_Renderer*& renderer, int, int);
	~BrickBall();
	void SetBrickBall(SDL_Window*& window, SDL_Renderer*& renderer,int ,int);
public:
	void PlayGame();
};


#pragma once
#include "LibGame.h"
#include <math.h>
#include <random>
#include <time.h> 
#include <SDL.h>
#include<SDL_image.h>
class Brick
{
	// CONST VALUE
//public:
//	// const for check collide
//	static const int BORDER_LEFT = 1;
//	static const int BORDER_RIGHT = 2;
//	static const int BORDER_TOP = 3;
//	static const int BORDER_BOTTOM = 4;
//	static const int BORDER_CORNER = 5;
public:
	static const int BRICK_LENGTH = 60;
	static const int BRICK_WIDTH = 30;
private:
	// Position
	SDL_Rect _rect;

	//
	bool is_exist;
	// SDL windows
	SDL_Renderer* _renderer;
	SDL_Surface* _surface;
	SDL_Texture* _texture;

public:
	Brick(SDL_Renderer* renderer, int x, int y);
	~Brick();
public:
	void SetRect(int x, int y);
	void Show();
};
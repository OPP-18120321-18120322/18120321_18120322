#pragma once
#include "BaseObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class MatchScore
{
public:
	static const int DEFAULT_WIDTH = 64;
	static const int DEFAULT_HEIGHT = 94;
	static const int POS_Y = 242;
	static const int POS_HUNDRED_X = 25;
	static const int POS_TEN_X = 89;
	static const int POS_ONE_X = 153;

private:
	vector<Object> _number;

	vector<SDL_Rect> _position;

	int _scores[3];

	SDL_Renderer* _render;
public:
	MatchScore(SDL_Renderer*& renderer);
public:
	void CalcScore(int score);
	void ShowScore();
};


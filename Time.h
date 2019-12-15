#pragma once
#include <SDL.h>
#include <SDL_timer.h>
#include <string>
#include "SDL_TextView.h"
#include <SDL_image.h>
#include <math.h>
class Time
{
private:
	SDL_Renderer* _render;

	int _start_tick;
	int _paused_tick;

	bool _is_paused;
	bool _is_started;
public:
	Time(int add_time);
public:
	void ShowTime();
	void StartTime(SDL_Renderer*& renderer);
	void StopTime();
	void PausedTime();
	void UnpausedTime();
	int GetTicks();
	bool IsStartedTime();
	bool IsPausedTime();

};


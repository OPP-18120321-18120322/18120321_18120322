#include "Time.h"

Time::Time(int add_time) {
	_start_tick = 0 + add_time;
	_paused_tick = 0;
	_is_paused = false;
	_is_started = false;
}

void Time::StartTime(SDL_Renderer*& renderer) {
	_render = renderer;
	_is_started = true;
	_is_paused = false;
	_start_tick = SDL_GetTicks();

}

void Time::StopTime() {
	_is_paused = true;
	_is_started = false;
}

void Time::PausedTime(){
	if (_is_started == true && _is_paused == false) {
		_is_paused = true;
		_paused_tick = SDL_GetTicks() - _start_tick;
	}
}

void Time::UnpausedTime() {
	if (_is_paused == true) {
		_is_paused = false;
		_start_tick = SDL_GetTicks() - _paused_tick;
		_paused_tick = 0;

	}
}

int Time::GetTicks() {
	if (_is_started == true) {
		if (_is_paused == true) {
			return _paused_tick;
		}
		else {
			return SDL_GetTicks() - _start_tick;
		}
	}

	return 0;
}

bool Time::IsStartedTime() {
	return _is_paused;
}

bool Time::IsPausedTime() {
	return _is_paused;
}

void Time::ShowTime() {
	string text_time;
	int time;
	string fontpath = "lib\\font\\mto yikes.ttf";
	time = GetTicks();
	time = (time / 1000) % 30;

	if (time == 0) {
		text_time = "00 : 00";
	}

	if (time >= 1 && time < 10) {
		text_time = "00 : 0" + to_string(time);
	}


	if (time >= 10) {
		text_time = "00 : " + to_string(time);

	}

	SDL_TextView text(_render, 85, 450, text_time, 28, fontpath, { 255,0,0,255 });
	text.Show();

}

#pragma once
#include"GamePingPong.h"

class MainMenu
{
private:
	bool _initSuccess;
	PingPong _pingpong;
	SDL_Window* _window;
	SDL_Renderer* _render;
public:
	// const 
	static const int DEFAULT_WIDTH = 1280;
	static const int DEFAULT_HEIGHT = 720;
	static const int DEFAULT_FPS = 60;

	// margin by pixel
	static const int MARGIN_TOP = 50;
	static const int MARGIN_BOTTOM = 50;
public:
	MainMenu();
	~MainMenu();
public:
	// Description: Create and Init SDL, TTF framework
	bool InitSDL(SDL_Window*&, SDL_Renderer*&, int, int);

	// Description: Free and close SDL, TTF framework
	void CloseSDL(SDL_Window*&, SDL_Renderer*&);
public:
	void Menu();
};


//#include <iostream>
//#include "MainGame.h"
//
//#define SDL_MAIN_HANDLED
//#include <SDL.h>
//
//using namespace std;
//int main() {
//
//	MainGame gamePlay;
//	//Initializes  the subsystems
//	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
//	{
//		printf("Unable to initialize SDL %s\n", SDL_GetError());
//		return -1;
//	}
//
//	//SDL_Window* window = NULL;
//	//window = SDL_CreateWindow("PING PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
//	//if (window == NULL)
//	//{
//	//	printf("Could not create window %s\n", SDL_GetError());
//	//	return -1;
//	//}
//	// game launcher already appeared from here
//
//	gamePlay.Play();
//
//	return 0;
//}

#include <SDL.h>
#include <SDL_image.h>


SDL_Window* g_windows = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* g_background = NULL;


bool loadMedia()
{
	bool success = true;
	g_background = IMG_Load("brick.png");
	if (g_background == NULL)
	{
		success = false;
	}

	return success;
}


void close()
{
	SDL_FreeSurface(g_background);
	g_background = NULL;
	SDL_DestroyWindow(g_windows);
	g_windows = NULL;
	SDL_Quit();
}

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		g_windows = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 960, SDL_WINDOW_SHOWN);
		if (g_windows != NULL)
		{
			gScreenSurface = SDL_GetWindowSurface(g_windows);
		}
	}
	return success;
}


int main(int argc, char* argv[])
{
	if (init() == true)
	{
		if (loadMedia())
		{
			SDL_BlitSurface(g_background, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(g_windows);
			SDL_Delay(2000);
		}
	}

	close();
	return 0;
}
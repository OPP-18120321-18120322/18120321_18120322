#include <iostream>
#include "GamePingPong.h"
#include"MainMenu.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>

using namespace std;
int main() {

	MainMenu main;
	//Initializes  the subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return -1;
	}

	//SDL_Window* window = NULL;
	//window = SDL_CreateWindow("PING PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	//if (window == NULL)
	//{
	//	printf("Could not create window %s\n", SDL_GetError());
	//	return -1;
	//}
	// game launcher already appeared from here

	main.Menu();

	return 0;
}


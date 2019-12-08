#include "MainMenu.h"

MainMenu::MainMenu()
{
	_initSuccess = InitSDL(_window, _render, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	_pingpong.SetPingPong(_window, _render);
}
MainMenu::~MainMenu()
{
	CloseSDL(_window, _render);
}
void MainMenu::Menu()
{
	//pingpong.PlayPingPong();
	cout << "1";
	_pingpong.PlayPingPong();
	cout << "2";
}

bool MainMenu::InitSDL(SDL_Window*& window, SDL_Renderer*& renderer, int SCREEN_WIDTH = DEFAULT_WIDTH, int SCREEN_HEIGHT = DEFAULT_HEIGHT)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("GAME D&D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize the truetype font API.
				if (TTF_Init() < 0)
				{
					SDL_Log("%s", TTF_GetError());
					return false;
				}
				else {
					//Initialize renderer color
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				}
			}
		}
	}
	return success;
}

void MainMenu::CloseSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Shutdown and cleanup the truetype font API.
	TTF_Quit();

	//Quit SDL subsystems
	SDL_Quit();
}
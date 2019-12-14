﻿#include "MainMenu.h"
#include "Highscores.h"
MainMenu::MainMenu()
{
	_initSuccess = InitSDL(_window, _render, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	_pingpong.SetPingPong(_window, _render);
	_brickball.SetBrickBall(_window, _render, 1280, 720);
	interface.LoadImg(_render, { 0,0,1280,720 }, "image//bkground//bk3.png");
}
MainMenu::~MainMenu()
{
	CloseSDL(_window, _render);
}
void MainMenu::PlayGame()
{
	bool isHandle = true;
	//bool isInMenu = true;
	int Selection = -1;
	Highscores rank(_render);
	while (isHandle)
	{
		//Load Menu:
		Selection = ShowMainMenu();
		switch (Selection)
		{
		case 1:
			//Chơi mới ->Chọn màn->Nhập tên->Load giao diện->Chơi
			cout << "1";
			_pingpong.PlayPingPong();
			break;
		case 2:
			//Chơi lại ->Load dữ liệu cũ ->Tiếp tục chơi
			cout << "2";
			_brickball.PlayGame();
			isHandle = false;
			break;
		case 3:
			//Hiển thị bản thành tích người chơi
			cout << "3";
			rank.ReadFile("players.txt");
			interface.ShowImg();
			rank.ShowHighscores();
			isHandle = false;
			break;
		case 4:
			//Option điều chỉnh ẩm thanh 
			cout << "4";
			isHandle = false;
			break;
		case 5:
			//Huong dan choi 
			cout << "5";
			isHandle = false;
			break; 
		case 6:
			//Exit
			cout << "6";
			isHandle = false;
			break;
		default:
			break;
		}
	}
}
int MainMenu::ShowMainMenu()
{
	int Mode = -1;
	bool isInMenu = true;
	vector<Object> objects;
	Object Selection;
	SDL_Event even;
	objects.push_back(Object::Object(_render, { 0,0,1280,720 }, "image//bkground//bk3.png"));
	objects.push_back(Object::Object(_render, { 800,100,340,541 }, "image//material//main_menu.png"));
	objects.push_back(Object::Object(_render, { 875,240,190,40 }, "image//button//button_newgame.png"));
	objects.push_back(Object::Object(_render, { 875,300,190,40 }, "image//button//button_loadgame.png"));
	objects.push_back(Object::Object(_render, { 875,360,190,40 }, "image//button//button_highscores.png"));
	objects.push_back(Object::Object(_render, { 875,420,190,40 }, "image//button//button_option.png"));
	objects.push_back(Object::Object(_render, { 875,480,190,40 }, "image//button//button_help.png"));
	objects.push_back(Object::Object(_render, { 875,540,190,40 }, "image//button//button_quit.png"));
	//objects.push_back(Object::Object(_render, { 0,0,25,25 }, "image//material//ball.png"));
	Selection.LoadImg(_render, { 875,540,190,40 }, "image//button//button_selected.png");
	//objects.push_back(Object::Object(_render, { 0,0,190,40 }, "image//button_selected.png"));
	/*Ball ball;
	Player player;
	ball.LoadImg(_render, { 240,540,25,25 }, "image//ball.png");
	player.LoadImg(_render, { 225,540,17,132 }, "image//Untitled.png");*/
	while (isInMenu)
	{
		

		while (SDL_PollEvent(&even))
		{
			for (int i = 2; i < 8; i++)
			{
				if (objects[i].ClickMouse(even))
				{
					Mode = i-1;
					Selection.SetRect(objects[i].Rect());
					Selection.ShowImg();
					isInMenu = false;
				}
			}
		}
		//Clear màn hình
		SDL_RenderClear(_render);
		for (auto object : objects) object.ShowImg();
		for (int i = 2; i < 8; i++)
		{
			if (objects[i].CheckMouseWithButton(even.motion.x, even.motion.y))
			{
				Selection.SetRect(objects[i].Rect());
				Selection.ShowImg();
			}
		}
		SDL_RenderPresent(_render);
		SDL_Delay(1000 / DEFAULT_FPS);
	}
	return Mode;
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
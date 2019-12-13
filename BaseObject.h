#pragma once
#include <SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"LibGame.h"
using namespace std;

class Object
{
protected:
	// SDL windows
	SDL_Rect _rect;

	// SDL windows
	SDL_Renderer* _renderer;
	SDL_Surface* _surface;
	SDL_Texture* _texture;
public:
	Object();
	Object(SDL_Renderer* renderer, SDL_Rect rect, string fileimg);
	~Object();
public:
	SDL_Rect Rect() { return _rect; }
	void SetRect(SDL_Rect rect) { _rect = rect; }
public:
	//Xử lý ảnh 
	void LoadImg(SDL_Renderer* renderer, SDL_Rect rect, string fileimg);
	void ShowImg();

	void ShowImgScore(SDL_Rect &rect);

	//Xử lý chuột 
	bool CheckMouseWithButton(int xmouse, int ymouse);
	bool ClickMouse(SDL_Event events);
};


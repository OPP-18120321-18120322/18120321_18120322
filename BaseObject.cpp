#include "BaseObject.h"

Object::Object()
{
	_rect.x = 0;
	_rect.y = 0;
	_rect.h = 720;
	_rect.w = 1280;
}
Object::Object(SDL_Renderer* renderer, SDL_Rect rect, string fileimg)
{
	_rect = rect;
	_renderer = renderer;
	_surface= IMG_Load(fileimg.c_str());
	_texture= SDL_CreateTextureFromSurface(_renderer, _surface);
}
Object::~Object()
{
	if (!_texture) SDL_DestroyTexture(_texture);
	if (!_surface) SDL_FreeSurface(_surface);
}

//Xử lý ảnh
void Object::LoadImg(SDL_Renderer* renderer, SDL_Rect rect, string fileimg)
{
	_rect = rect;
	_renderer = renderer;
	_surface = IMG_Load(fileimg.c_str());
	_texture = SDL_CreateTextureFromSurface(_renderer, _surface);
}
void Object::ShowImg()
{
	SDL_RenderCopy(_renderer, _texture, NULL, &_rect);
}

void Object::ShowImgWithRect(SDL_Rect &rect) {
	SDL_RenderCopy(_renderer, _texture, NULL, &rect);
}

//Xử lý chuột
bool Object::CheckMouseWithButton(int xmouse, int ymouse)
{

	if (xmouse >= _rect.x && xmouse <= _rect.x + _rect.w && ymouse >= _rect.y && ymouse <= _rect.y + _rect.h)
	{
		return true;
	}
	return false;
}
bool Object::ClickMouse(SDL_Event events)
{
	int xmouse = 0;
	int ymouse = 0;
	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_LEFT)
		{

			xmouse = events.motion.x;
			ymouse = events.motion.y;

			if (CheckMouseWithButton(xmouse, ymouse))
				return true;
		}
	}
	return false;
}
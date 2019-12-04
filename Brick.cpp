#include "Brick.h"

#include "Brick.h"

Brick::Brick(SDL_Renderer* renderer, int x, int y)
{
	is_exist = true;

	_rect.x = x;
	_rect.y = y;
	_rect.w = BRICK_WIDTH;
	_rect.h = BRICK_LENGTH;

	_renderer = renderer;
	_surface = IMG_Load("brick.png");


	_texture = SDL_CreateTextureFromSurface(_renderer, _surface);
}
Brick::~Brick()
{
	if (!_texture) SDL_DestroyTexture

	(_texture);
	if (!_surface) SDL_FreeSurface(_surface);
}
void Brick::SetRect(int x, int y)
{
	_rect.x = x;
	_rect.y = y;
	_rect.w = BRICK_WIDTH;
	_rect.h = BRICK_LENGTH;
}
void Brick::Show()
{
	if (is_exist)
		SDL_RenderCopy(_renderer, _texture, NULL, &_rect);
}
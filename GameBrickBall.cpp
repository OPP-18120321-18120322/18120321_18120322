#include "GameBrickBall.h"

void BrickBall::Init()
{
	_interfaces.push_back(Object::Object(_render, { 0,0,1280,720 },"image//bkground//bk1.png"));
}
BrickBall::BrickBall()
{
	_width = DEFAULT_WIDTH;
	_height = DEFAULT_HEIGHT;


	_ball.LoadImg(_render, { 280,0,25,25 }, "image//material//ball.png");
	_player.LoadImg(_render, { BORDER_LEFT + MARGIN,(_height - 132) / 2,21,132 }, "image//material//scrollbar.png");

	Init();
}
BrickBall::BrickBall(SDL_Window*& window, SDL_Renderer*& renderer, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT)
{
	_width = width;
	_height = height;

	_window = window;
	_render = renderer;

	_ball.LoadImg(_render, { 280,MARGIN,25,25 }, "image//material//ball.png");
	_player.LoadImg(_render, { BORDER_LEFT + MARGIN,(_height - 132) / 2,21,132 }, "image//material//scrollbar.png");

	Init();

}
void BrickBall::SetBrickBall(SDL_Window*& window, SDL_Renderer*& renderer, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT)
{
	_window = window;
	_render = renderer;

	_width = width;
	_height = height;

	_window = window;
	_render = renderer;

	_ball.LoadImg(_render, { 280,MARGIN,25,25 }, "image//material//ball.png");
	_player.LoadImg(_render, { BORDER_LEFT + MARGIN,(_height-132)/2,21,132 }, "image//material//scrollbar.png");
	Init();
	
}
BrickBall::~BrickBall()
{
	//do st
}
void BrickBall::PlayGame()
{
	bool is_playing = true;

	Uint8* keyboardState = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));

	while (is_playing) 
	{
		// Di chuyển thanh trượt 
		if (keyboardState[SDL_SCANCODE_S])
		{
			cout << "1";
			if (_player.Pos().y + _player.Length() + _player.Speed() <= _height - MARGIN)
			{
				_player.Move(Player::MOVE_DOWN);
			}
		}
		else if (keyboardState[SDL_SCANCODE_W])
		{
			cout << "2";
			if (_player.Pos().y - _player.Speed() >= 0 + MARGIN)
			{
				_player.Move(Player::MOVE_UP);
			}
		}

		//Va chạm thanh trượt 
		/*if (_ball.Center().x <= _player.Pos().x + _player.Width()
			&& _ball.Center().y >= _player.Pos().y
			&& _ball.Center().y <= _player.Pos().y + _player.Length())
		{
			_ball.Collide(Ball::BORDER_LEFT);
			_ball.LevelUp();

		}*/
		//va chạm tường phải
		if (_ball.Center().x <= _player.Pos().x + _player.Width())
		{
			_ball.Collide(Ball::BORDER_LEFT);
		}
		//va chạm tường phải
		if (_ball.Center().x >= _width - 2*_ball.Radius() - MARGIN)
		{
			_ball.Collide(Ball::BORDER_RIGHT);
		}

		//collide wall
		if (_ball.Center().y <= 0  + MARGIN) {
			_ball.Collide(Ball::BORDER_TOP);
		}
		if (_ball.Center().y >= _height - 2*_ball.Radius() - MARGIN) {
			_ball.Collide(Ball::BORDER_BOTTOM);
		}

		//Va cham nổ
		if (_ball.Center().x <= _player.Pos().x && _ball.Center().y <= _player.Pos().y
			&& _ball.Center().y >= _player.Pos().y + _player.Length()) {
			cout << "1";
			is_playing = false;
		}
		
		_ball.Move();
		SDL_RenderClear(_render);

		for (auto interface :_interfaces) interface.ShowImg();
		_ball.ShowImg();
		_player.ShowImg();

		SDL_RenderPresent(_render);
		SDL_Delay(1000 / DEFAULT_FPS);
	}
}
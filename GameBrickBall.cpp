#include "GameBrickBall.h"

void BrickBall::InitData()
{
	is_playing = true;
	heart = 3;

	_ball.LoadImg(_render, { BORDER_LEFT + MARGIN + 21,(_height - 132) / 2 + 56,20,20 }, "image//material//ball.png");
	_player.LoadImg(_render, { BORDER_LEFT + MARGIN,(_height - 132) / 2,21,132 }, "image//material//scrollbar.png");

	_maze.SetMap(_render, "image//material//item5.png", 7);

	img_hearts.push_back(Object::Object(_render, { 60,390,35,35 }, "image//material//heart.png"));
	img_hearts.push_back(Object::Object(_render, { 105,390,35,35 }, "image//material//heart.png"));
	img_hearts.push_back(Object::Object(_render, { 150,390,35,35 }, "image//material//heart.png"));
}

void BrickBall::RestoreData()
{
	is_playing = true;
	heart = 3;
	_ball.Restore({ BORDER_LEFT + MARGIN + 21,(_height - 132) / 2 + 56 });
	_player.Restore({ BORDER_LEFT + MARGIN,(_height - 132) / 2 });
	_maze.SetMap(_render, "image//material//item5.png", 7);
}
BrickBall::BrickBall()
{
	_width = DEFAULT_WIDTH;
	_height = DEFAULT_HEIGHT;
	_score = 0;
}

BrickBall::BrickBall(SDL_Window*& window, SDL_Renderer*& renderer, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT)
{
	_width = width;
	_height = height;
	_score = 0;

	_window = window;
	_render = renderer;

	_interfaces.push_back(Object::Object(_render, { 0,0,1280,720 }, "image//bkground//bk2.png"));

	InitData();

}

void BrickBall::SetBrickBall(SDL_Window*& window, SDL_Renderer*& renderer, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT)
{
	_window = window;
	_render = renderer;

	_width = width;
	_height = height;
	_score = 0;

	_window = window;
	_render = renderer;

	_interfaces.push_back(Object::Object(_render, { 0,0,1280,720 }, "image//bkground//bk2.png"));

	InitData();
}

BrickBall::~BrickBall()
{
	//do st
}

void BrickBall::PlayGame()
{

	SDL_Event e;
	int Mode;
	bool isPressed = false;
	Uint8* keyboardState = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
	int speed = 0;
	is_quit = false;


	while (!is_quit) {
		Mode = ShowMenu();
		if (Mode == 3)
		{
			is_quit = true;
			break;
		}
		while (is_playing)
		{

			// Di chuyển thanh trượt 
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type)
				{

				case SDL_KEYDOWN: {
					isPressed = true;
					break;
				}
				case SDL_KEYUP: {
					isPressed = false;
					speed = 0;
					break;
				}
				default:
					break;
				}

			}
			if (isPressed)
			{
				if (keyboardState[SDL_SCANCODE_S])
				{
					if (_player.Pos().y + _player.Length() + _player.Speed() <= _height - MARGIN)
					{
						_player.Move(Player::MOVE_DOWN);
						speed = _player.Speed();
					}
				}
				else if (keyboardState[SDL_SCANCODE_W])
				{
					if (_player.Pos().y - _player.Speed() >= 0 + MARGIN)
					{
						_player.Move(Player::MOVE_UP);
						speed = -_player.Speed();
					}
				}
				else if (keyboardState[SDL_SCANCODE_P])
				{
					
				}
			}

			//Va chạm thanh trượt 
			if (_ball.Center().x <= _player.Pos().x + _player.Width() && _ball.Center().y + _ball.Radius() >= _player.Pos().y && _ball.Center().y + _ball.Radius() <= _player.Pos().y + _player.Length())
			{
				//_ball.Collide(Ball::BORDER_LEFT, speed);
				_ball.Collide(Ball::BORDER_LEFT, 0);
				_ball.LevelUp();
				speed = 0;

			}

			if (_ball.Center().x >= _width - 2 * _ball.Radius() - MARGIN)
			{
				_ball.Collide(Ball::BORDER_RIGHT);
			}

			//collide wall
			if (_ball.Center().y <= 0 + MARGIN) {
				_ball.Collide(Ball::BORDER_TOP);
			}
			if (_ball.Center().y >= _height - 2 * _ball.Radius() - MARGIN) {
				_ball.Collide(Ball::BORDER_BOTTOM);
			}
			//Va cham gach
			HandleCollideBrick();
			//Va cham nổ
			if (_ball.Center().x <= _player.Pos().x && (_ball.Center().y +_ball.Radius() < _player.Pos().y || _ball.Center().y + _ball.Radius() > _player.Pos().y + _player.Length()))
			{
				heart--;
				if (heart <= 0)
				{
					is_playing = false;
					continue;
				}
				_ball.Restore({ _player.Pos().x+_player.Width(),_player.Pos().y+_player.Length()/2-_ball.Radius()});
			}
			if (is_playing == false)
			{
				HandleWinLose();
				continue;
			}

			_ball.Move();
			SDL_RenderClear(_render);

			for (auto interface :_interfaces) interface.ShowImg();
			_ball.ShowImg();
			_player.ShowImg();
			_maze.ShowMap();
			for (int i = 0; i < heart; i++)
			{
				img_hearts[i].ShowImg();
			}
			SDL_RenderPresent(_render);
			SDL_Delay(1000 / DEFAULT_FPS);

		}
		RestoreData();
	}
}
void BrickBall::HandleCollideBrick()
{
	int count = 0;
	vector<Brick> brick;
	for (int i = 0; i < Maze::NUMBER_ROW; i++)
	{
		brick = _maze.MazeBrick(i);
		for (int j = 0; j < Maze::NUMBER_COLUMN; j++)
		{
			if (brick[j].IsExist())
			{

				if (_ball.Center().x + 2 * _ball.Radius() >= brick[j].Pos().x && _ball.Center().x + 2 * _ball.Radius() <= brick[j].Pos().x + Brick::BRICK_LENGTH
					&& _ball.Center().y + _ball.Radius() >= brick[j].Pos().y && _ball.Center().y + _ball.Radius() <= brick[j].Pos().y + Brick::BRICK_LENGTH)
				{

					_ball.Collide(Ball::BORDER_RIGHT);
					_maze.MazeBrick(i)[j].SetExist(0);
					_score += 3;
					break;
				}
				else if (_ball.Center().x >= brick[j].Pos().x && _ball.Center().x <= brick[j].Pos().x + Brick::BRICK_LENGTH
					&& _ball.Center().y + _ball.Radius() >= brick[j].Pos().y && _ball.Center().y + _ball.Radius() <= brick[j].Pos().y + Brick::BRICK_LENGTH)
				{
					_ball.Collide(Ball::BORDER_LEFT);
					_maze.MazeBrick(i)[j].SetExist(0);
					_score += 3;
					break;
				}
				else if (_ball.Center().x + _ball.Radius() >= brick[j].Pos().x && _ball.Center().x + _ball.Radius() <= brick[j].Pos().x + Brick::BRICK_LENGTH
					&& _ball.Center().y >= brick[j].Pos().y && _ball.Center().y <= brick[j].Pos().y + Brick::BRICK_LENGTH)
				{
					_ball.Collide(Ball::BORDER_TOP);
					_maze.MazeBrick(i)[j].SetExist(0);
					_score += 3;
					break;
				}
				else if (_ball.Center().x + _ball.Radius() >= brick[j].Pos().x && _ball.Center().x + _ball.Radius() <= brick[j].Pos().x + Brick::BRICK_LENGTH
					&& _ball.Center().y + 2 * _ball.Radius() >= brick[j].Pos().y && _ball.Center().y + 2 * _ball.Radius() <= brick[j].Pos().y + Brick::BRICK_LENGTH)
				{
					_ball.Collide(Ball::BORDER_BOTTOM);
					_maze.MazeBrick(i)[j].SetExist(0);
					_score += 3;
					break;
				}
			}
			else
				count++;
			if (count >= Maze::NUMBER_COLUMN * Maze::NUMBER_ROW)
			{
				is_playing = false;
			}
		}
	}
}
int BrickBall::ShowMenu()
{
	int Mode = -1;
	SDL_Event even;
	bool isInMenu = true;
	vector<Object> objects;
	objects.push_back(Object::Object(_render, { 0,0,1280,720 }, "image//bkground//bk.png"));
	objects.push_back(Object::Object(_render, { (1280 - 340) / 2,(720 - 340) / 2,340,340 }, "image//material//main_menu.png"));
	objects.push_back(Object::Object(_render, { (1280 - 340) / 2 + 75,300,190,40 }, "image//button//button_newgame.png"));
	objects.push_back(Object::Object(_render, { (1280 - 340) / 2 + 75,360,190,40 }, "image//button//button_loadgame.png"));
	objects.push_back(Object::Object(_render, { (1280 - 340) / 2 + 75,420,190,40 }, "image//button//button_quit.png"));

	Object Selection;
	Selection.LoadImg(_render, { 875,540,190,40 }, "image//button//button_selected.png");

	while (isInMenu)
	{
		while (SDL_PollEvent(&even))
		{
			for (int i = 2; i < 5; i++)
			{
				if (objects[i].ClickMouse(even))
				{
					Mode = i - 1;
					isInMenu = false;
				}
			}
		}
		//Clear màn hình
		SDL_RenderClear(_render);
		for (auto object : objects) object.ShowImg();
		for (int i = 2; i < 5; i++)
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
void BrickBall::PauseGame()
{
	
}
void BrickBall::HandleWinLose()
{
	;
}
#include "GameBrickBall.h"

#include "MatchScore.h"
#include "Maze.h"

void BrickBall::InitData()
{
	
	is_playing = true;
	heart = 3;

	_ball.LoadImg(_render, { BORDER_LEFT + MARGIN + 21,(_height - 132) / 2 + 56,20,20 }, "image//material//ball.png");
	_player.LoadImg(_render, { BORDER_LEFT + MARGIN,(_height - 132) / 2,21,132 }, "image//material//scrollbar.png");

	srand((int)time(0));
	num = 1 + rand() % 8;
	_maze.SetMap(_render, "image//material//item5.png", num);
	int num_avatar;
	num_avatar= 1 + rand() % 14;
	avatar.LoadImg(_render, { 5,20,65,65 }, "image//avatar//avt" + to_string(num_avatar) + ".png");

	music = Mix_LoadMUS("sound//soundtrack_christmas.mp3");
	
	start = true;
	
}
bool BrickBall::LoadData()
{
	int empty;
	is_playing = true;
	int x, y;
	num = 0;
	_maze.SetMap(_render, "image//material//item5.png", num);
	fstream file("data//data_user.txt", ios::in);
	file >> empty;
	if (empty == 1)
		return false;
	file >> _score;
	file >> heart;
	file >> x;
	file >> y;
	cout << x << " " << y;
	_player.LoadImg(_render, { x,y,21,132 }, "image//material//scrollbar.png");
	file >> x;
	file >> y;
	_ball.LoadImg(_render, { x,y,20,20 }, "image//material//ball.png");
	file.close();

	fstream file_empty("data//data_user.txt", ios::out);
	file_empty << "1";
	file_empty.close();

	music = Mix_LoadMUS("sound//soundtrack_christmas.mp3");
	
	start = true;

	return true;
}
void BrickBall::RestoreData()
{
	is_playing = true;
	heart = 3;
	_score = 0;
	_ball.Restore({ BORDER_LEFT + MARGIN + 21,(_height - 132) / 2 + 56 });
	_player.Restore({ BORDER_LEFT + MARGIN,(_height - 132) / 2 });
	srand((int)time(0));
	num = 1 + rand() % 8;
	_maze.SetMap(_render, "image//material//item5.png", num);
	
	start = true;
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

	img_hearts.push_back(Object::Object(_render, { 60,385,35,35 }, "image//material//heart.png"));
	img_hearts.push_back(Object::Object(_render, { 105,385,35,35 }, "image//material//heart.png"));
	img_hearts.push_back(Object::Object(_render, { 150,385,35,35 }, "image//material//heart.png"));

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

	img_hearts.push_back(Object::Object(_render, { 60,385,35,35 }, "image//material//heart.png"));
	img_hearts.push_back(Object::Object(_render, { 105,385,35,35 }, "image//material//heart.png"));
	img_hearts.push_back(Object::Object(_render, { 150,385,35,35 }, "image//material//heart.png"));
	//InitData();
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
	MatchScore Score(_render);

	while (!is_quit) 
	{
		ShowMenu();
		while (is_playing)
		{

			while (start)
			{
				chunk = Mix_LoadWAV("sound//GetReady.wav");
				Mix_PlayChannel(-1, chunk, 0);
				SDL_Delay(300);
				chunk = Mix_LoadWAV("sound//hieulenh.wav");
				Mix_PlayChannel(-1, chunk, 0);
				Object wait;
				for (int i = 0; i < 3; i++)
				{
					wait.LoadImg(_render, { 0,0,1280,720 }, "image//material//wait_" + to_string(i + 1) + ".png");
					SDL_RenderClear(_render);

					for (auto interface :_interfaces) interface.ShowImg();
					avatar.ShowImg();
					_ball.ShowImg();
					_player.ShowImg();
					_maze.ShowMap();
					for (int i = 0; i < heart; i++)
					{
						img_hearts[i].ShowImg();
					}
					wait.ShowImg();
					SDL_RenderPresent(_render);
					SDL_Delay(1000);
				}
				Mix_PlayMusic(music, -1);
				start = false;
			}

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
					PauseGame();
				}
			}

			//Va chạm thanh trượt 
			if (_ball.Center().x <= _player.Pos().x + _player.Width() && _ball.Center().y + _ball.Radius() >= _player.Pos().y && _ball.Center().y + _ball.Radius() <= _player.Pos().y + _player.Length())
			{
				//_ball.Collide(Ball::BORDER_LEFT, speed);
				chunk = Mix_LoadWAV("sound//Bounce.wav");
				Mix_PlayChannel(-1, chunk, 0);
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
			Score.CalcScore(_score);
			
			//Va cham nổ
			if (_ball.Center().x <= _player.Pos().x && (_ball.Center().y +_ball.Radius() < _player.Pos().y || _ball.Center().y + _ball.Radius() > _player.Pos().y + _player.Length()))
			{
				heart--;
				if (heart <= 0)
				{
					is_playing = false;
				}
				else {
					SDL_Delay(100);
					_ball.Restore({ _player.Pos().x + _player.Width(),_player.Pos().y + _player.Length() / 2 - _ball.Radius() });
				}
			}
			SDL_RenderClear(_render);

			for (auto interface :_interfaces) interface.ShowImg();
			avatar.ShowImg();
			_ball.ShowImg();
			_player.ShowImg();
			_maze.ShowMap();

			for (int i = 0; i < heart; i++)
			{
				img_hearts[i].ShowImg();
			}
			Score.ShowScore();
			SDL_RenderPresent(_render);
			SDL_Delay(1000 / DEFAULT_FPS);
			
			if (is_quit == true)
			{
				RestoreData();
				return;
			}
			if (is_playing == false)
			{
				Mix_HaltMusic();
				HandleWinLose();
			}
			_ball.Move();
			
			
		}
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
void BrickBall::ShowMenu()
{
	int Mode = -1;
	SDL_Event even;
	bool isInMenu = true;
	vector<Object> objects;
	objects.push_back(Object::Object(_render, { 0,0,1280,720 }, "image//bkground//bk.png"));

	objects.push_back(Object::Object(_render, { (1280 - 340) / 2,(720 - 340) / 2,340,340 }, "image//material//menu.png"));
	objects.push_back(Object::Object(_render, { (1280 - 340) / 2 + 75,300,190,40 }, "image//button//button_newgame.png"));
	objects.push_back(Object::Object(_render, { (1280 - 340) / 2 + 75,360,190,40 }, "image//button//button_loadgame.png"));
	objects.push_back(Object::Object(_render, { (1280 - 340) / 2 + 75,420,190,40 }, "image//button//button_quit.png"));

	Object Selection;
	Selection.LoadImg(_render, { 875,540,190,40 }, "image//button//button_selected.png");
	music = Mix_LoadMUS("sound//wait.mp3");
	
	Mix_PlayMusic(music, -1);
	while (isInMenu)
	{
		
		while (SDL_PollEvent(&even))
		{
			for (int i = 2; i < 5; i++)
			{
				if (objects[i].ClickMouse(even))
				{
					Mode = i - 1;
					switch (Mode) {
					case 1:
						InitData();
						Mix_HaltMusic();
						return;
					case 2:
						if (LoadData() == true)
						{
							Mix_HaltMusic();
							return;
						}
						break;
					case 3:
						is_quit = true;
						is_playing = false;
						return;
					default:
						break;
					}
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

}
void BrickBall::PauseGame()
{
	int Mode = -1;
	SDL_Event even;
	bool IsPause = true;
	vector<Object> objects;
	objects.push_back(Object::Object(_render, { (1040 - 350) / 2 + BORDER_LEFT,(720 - 260) / 2,350,260 }, "image//material//menu_option.png"));
	objects.push_back(Object::Object(_render, { (1040 - 350) / 2 + 75 + BORDER_LEFT,280,190,40 }, "image//button//button_resume.png"));
	objects.push_back(Object::Object(_render, { (1040 - 350) / 2 + 75 + BORDER_LEFT,340,190,40 }, "image//button//button_savegame.png"));
	objects.push_back(Object::Object(_render, { (1040 - 350) / 2 + 75 + BORDER_LEFT,400,190,40 }, "image//button//button_quit.png"));

	Object Selection;
	Selection.LoadImg(_render, { 875,540,190,40 }, "image//button//button_selected.png");
	while (IsPause)
	{
		while (SDL_PollEvent(&even))
		{
			for (int i = 1; i < 4; i++)
			{
				if (objects[i].ClickMouse(even))
				{
					Mode = i;
					IsPause = false;
				}
			}
		}
		

		SDL_RenderClear(_render);

		for (auto interface :_interfaces) interface.ShowImg();
		avatar.ShowImg();
		_ball.ShowImg();
		_player.ShowImg();
		_maze.ShowMap();

		for (auto object : objects) object.ShowImg();


		for (int i = 1; i < 4; i++)
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
	switch (Mode) {
	case 1:
		break;
	case 2:
		SaveGame();
		break;
	case 3:
		is_quit = true;
		break;
	default:
		break;
	}
		
}
void BrickBall::SaveGame()
{
	fstream file("data//data_user.txt", ios::out);
	file << "0" << " ";
	file << _score<<" ";
	file << heart << " ";
	file << _player.Pos().x << " " << _player.Pos().y <<" ";
	file << _ball.Center().x << " " << _ball.Center().y << endl;
	file.close();
	_maze.WriteData("Maze//maze0.txt");
}
void BrickBall::HandleWinLose()
{

	int Mode = -1;
	SDL_Event even;
	bool IsWinLose = true;

	vector<Object> objects;
	objects.push_back(Object::Object(_render, { (1040 - 350) / 2 + BORDER_LEFT,(720 - 260) / 2,350,260 }, "image//material//menu_option.png"));
	objects.push_back(Object::Object(_render, { (1040 - 350) / 2 + 75 + BORDER_LEFT,340,190,40 }, "image//button//button_playagain.png"));
	objects.push_back(Object::Object(_render, { (1040 - 350) / 2 + 75 + BORDER_LEFT,400,190,40 }, "image//button//button_quit.png"));
	
	Object Selection;
	Selection.LoadImg(_render, { 875,540,190,40 }, "image//button//button_selected.png");

	Object Result;
	if (heart > 0)
	{
		chunk = Mix_LoadWAV("sound//Soundwin.wav");
		Mix_PlayChannel(-1, chunk, 0);
		Result.LoadImg(_render, { (1040 - 380) / 2 + BORDER_LEFT - 10,150,380,190 }, "image//material//win.png");
	}
	else {
		chunk = Mix_LoadWAV("sound//Soundlose.wav");
		Mix_PlayChannel(-1, chunk, 0);
		Result.LoadImg(_render, { (1040 - 380) / 2 + BORDER_LEFT - 10,150,380,190 }, "image//material//lose.png");
	}
	while (IsWinLose) 
	{
		while (SDL_PollEvent(&even))
		{
			for (int i = 1; i < 3; i++)
			{
				if (objects[i].ClickMouse(even))
				{
					Mode = i;
					IsWinLose = false;
				}
			}
		}


		SDL_RenderClear(_render);

		for (auto interface :_interfaces) interface.ShowImg();
		avatar.ShowImg();
		_ball.ShowImg();
		_player.ShowImg();
		_maze.ShowMap();
		

		for (auto object : objects) object.ShowImg();

		Result.ShowImg();
		for (int i = 1; i < 3; i++)
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
	switch (Mode) {
	case 1:
		RestoreData();
		break;
	case 2:
		is_quit = true;
		break;
	default:
		break;
	}
}

void BrickBall::ShowImg()
{
	SDL_RenderClear(_render);

	for (auto interface :_interfaces) interface.ShowImg();
	avatar.ShowImg();
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


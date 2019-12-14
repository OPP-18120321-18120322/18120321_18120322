#pragma once
#include "LibGame.h"
#include <math.h>
#include <random>
#include <time.h>   //for random
//#include"BaseObject.h"

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include<SDL_image.h>
using namespace std;
class Ball
{
// CONST VALUE
public:
	// const for check collide
	static const int BORDER_LEFT = 1;
	static const int BORDER_RIGHT = 2;
	static const int BORDER_TOP = 3;
	static const int BORDER_BOTTOM = 4;
	static const int BORDER_CORNER = 5;

	// const for speed per FPS
	static const int MAX_SPEED = 25;

private:
	// Position
	SDL_Rect _center;
	int _radius;


	// SDL windows
	SDL_Renderer* _render;
	SDL_Surface* _surface;
	SDL_Texture* _texture;
	// Vector speed
	float _i;
	float _j;

	float _speed;


// private method
private:
	void SyncSpeed();

// Getter and Setter
public:
	SDL_Rect Center() { return _center; };
	int Radius() { return _radius; };

	float AxisI() { return _i; };
	float AxisJ() { return _j; };
	int Speed() { return (int)_speed; };

	

// method
public:

	// Description: Directional the vector speed to right way 
	bool Collide(int, int = 0);

	// Description: Make the ball move one step 
	void Move();

	// Description: Show the ball to the board 
	void Draw();
	
	// Description: Increase speed of the ball
	void LevelUp();

// constructor and destructor
public:

	// Description: Default init
	Ball();

	// Description: Init tha ball with default pos, radius and vector speed
	Ball(SDL_Renderer* render, Point firstLocation, int radius);

	~Ball();

public:
	void LoadImg(SDL_Renderer* renderer, SDL_Rect rect, string fileimg);
	void ShowImg();
	void Restore(Point);
};

// Description: Create and fill a cricle with given RGBA color 
void Fill_circle(SDL_Renderer* render, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

//Desciption: Draw a circle with given RGBA color
void DrawCircle(SDL_Renderer* render, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

//Desctiption: Random axits for ball
void RandIandJ(float& i, float& j);
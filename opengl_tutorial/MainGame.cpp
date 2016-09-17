#include "MainGame.h"



MainGame::MainGame()
{
	_window = nullptr;
	_width = 800;
	_height = 400;
}


MainGame::~MainGame()
{
}

void MainGame::InitSystem()
{
	//initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("opengl tutorial",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, 
		_height, 
		SDL_WINDOW_OPENGL);
}

void MainGame::run()
{
	InitSystem();
}

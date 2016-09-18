#include "MainGame.h"
#include <iostream>

MainGame::MainGame()
{
	_window = nullptr;
	_width = 800;
	_height = 400;
	_gameState = GateState::PLAY;
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
	gameLoop();
}

void MainGame::gameLoop()
{
	while (_gameState != GateState::EXIT)
	{
		processInput();
	}
}
void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GateState::EXIT;
			break;
		case SDL_MOUSEMOTION:
		std::cout << evnt.motion.x << "," << evnt.motion.y << std::endl;
			break;
		}
	}
	
}

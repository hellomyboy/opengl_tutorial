#include "MainGame.h"
#include <iostream>
#include <string>
#include "Sprite.h"
#include "Error.h"



MainGame::MainGame()
{
	_window = nullptr;
	_width = 1024;
	_height = 768;
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

	if (_window == nullptr)
	{
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		fatalError("SDL Context could not be created!");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Could not initialize glew");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	initShaders();
}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("shaders/colorshading.vert", "shaders/colorshading.frag");
	_colorProgram.linkShaders();
	_colorProgram.addAttribue("vertexPosoiton");
}

void MainGame::run()
{
	InitSystem();
	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);
	gameLoop();
}

void MainGame::gameLoop()
{
	while (_gameState != GateState::EXIT)
	{
		processInput();
		drawGame();
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

// https://www.youtube.com/watch?v=8t3m2mRH7qs&list=PLSPw4ASQYyymu3PfG9gxywSPghnSMiOAW&index=6

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	_sprite.draw();

	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);
}

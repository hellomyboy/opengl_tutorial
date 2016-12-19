#include "MainGame.h"
#include <iostream>
#include <string>
#include <gameEngine\Engine.h>
#include <gameEngine/Sprite.h>
#include <gameEngine/Error.h>

#include <vector>
#include <gameEngine/IOManager.h>
#include <gameEngine/LoadImage.h>

MainGame::MainGame() :
	_width(1024),
	_height(768),
	_gameState(GameState::PLAY),
	_time(0.0f),
	_maxFPS(60.0)
{
}

MainGame::~MainGame()
{
}

void MainGame::InitSystem()
{
	Engine::init();

	_window.create("opengl tutorial", _width, _height, 0);

	initShaders();
}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("shaders/colorshading.vert", "shaders/colorshading.frag");
	_colorProgram.linkShaders();
	_colorProgram.addAttribue("vertexPosoiton");
	_colorProgram.addAttribue("vertexColor");
	_colorProgram.addAttribue("vertexUV");
}

void MainGame::run()
{
	InitSystem();

	_sprites.push_back(new Engine::Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "textures\\jimmyJump_pack\\PNG\\CharacterRight_Standing.png");
	std::cout << "first sprite" << std::endl;

	_sprites.push_back(new Engine::Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "textures\\jimmyJump_pack\\PNG\\CharacterRight_Standing.png");
	std::cout << "second sprite" << std::endl;

	_sprites.push_back(new Engine::Sprite());
	_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "textures\\jimmyJump_pack\\PNG\\CharacterRight_Standing.png");
	std::cout << "third sprite" << std::endl;

	gameLoop();
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		float startTicks = SDL_GetTicks();

		processInput();
		_time += 0.005;
		drawGame();

		static int frameCounter = 0;
		frameCounter++;
		calculateFPS();

		if (frameCounter == 20)
		{
			std::cout << "fps:" << _fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000 / _maxFPS > frameTicks) {
			SDL_Delay(1000 / _maxFPS - frameTicks);
		}
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
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << "," << evnt.motion.y << std::endl;
			break;
		}
	}
}

// https://www.youtube.com/watch?v=dNNXeMeF6yk&index=20&list=PLSPw4ASQYyymu3PfG9gxywSPghnSMiOAW

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	glActiveTexture(GL_TEXTURE0);
	GLint uvLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(uvLocation, 0);

	for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	}

	_colorProgram.unuse();

	//SDL_GL_SwapWindow(_window);
	_window.swapWindow();
}

void MainGame::calculateFPS()
{
	static const int NUM_FRAME_BUFF = 10;
	static float frameTime[NUM_FRAME_BUFF];
	static int buffIndex = 0;
	static float prevTicks = SDL_GetTicks();

	float currentTicks = SDL_GetTicks();
	frameTime[buffIndex % NUM_FRAME_BUFF] = currentTicks - prevTicks;
	prevTicks = currentTicks;
	buffIndex++;

	int count = 0;
	if (buffIndex > NUM_FRAME_BUFF) {
		count = NUM_FRAME_BUFF;
	} else {
		count = buffIndex;
	}

	float frameTimeSum = 0.0;
	for (int i = 0; i < count; i++) {
		frameTimeSum += frameTime[i];
	}
	float averageTime = frameTimeSum / count;

	if (averageTime > 0) {
		_fps = 1000.0 / averageTime;	//SDL_GetTicks() return ms
	} else {
		_fps = 0;
	}
}

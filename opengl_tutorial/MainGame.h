#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include "GLSLProgram.h"

enum class GateState
{
	PLAY,
	EXIT
};
class MainGame
{
public:
	MainGame();
	~MainGame();

	void gameLoop();
	void processInput();
	void drawGame();

	void InitSystem();
	void initShaders();
	void run();

private:
	SDL_Window* _window;
	int _width;
	int _height;
	GateState _gameState;

	Sprite _sprite;
	GLSLProgram _colorProgram;
};


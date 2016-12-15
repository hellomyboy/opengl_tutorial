#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <vector>

enum class GameState
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

	void calculateFPS();

private:
	SDL_Window* _window;
	int _width;
	int _height;
	GameState _gameState;

	std::vector<Sprite*> _sprites;
	//Sprite _sprite;
	GLSLProgram _colorProgram;

	//GLTexture _playerTexture;

	float _fps;
	float _maxFPS;

	float _time;
};


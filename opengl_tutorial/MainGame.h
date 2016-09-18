#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

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

	void InitSystem();
	void run();

private:
	SDL_Window* _window;
	int _width;
	int _height;
	GateState _gameState;
};


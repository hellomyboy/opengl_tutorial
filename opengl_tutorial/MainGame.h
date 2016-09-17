#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

class MainGame
{
public:
	MainGame();
	~MainGame();

	void InitSystem();
	void run();

private:
	SDL_Window* _window;
	int _width;
	int _height;
};


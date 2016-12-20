#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <gameEngine/Sprite.h>
#include <gameEngine/GLSLProgram.h>
#include <gameEngine/GLTexture.h>
#include <vector>
#include <gameEngine\Window.h>

#include <gameEngine\Camera2D.h>

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
	Engine::Window _window;
	int _width;
	int _height;
	GameState _gameState;

	std::vector<Engine::Sprite*> _sprites;
	//Sprite _sprite;
	Engine::GLSLProgram _colorProgram;

	//GLTexture _playerTexture;

	float _fps;
	float _maxFPS;

	float _time;

	Engine::Camera2D _camera2D;
};


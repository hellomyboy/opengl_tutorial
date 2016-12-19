#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>

namespace Engine {

	enum WindowFlags { INVISIABLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int windowWidth, int windowHeight, unsigned int flags);

		void swapWindow();

		int getWidth() {
			return _windowWidth;
		}

		int getHeight() {
			return _windowHeight;
		}

	private:
		SDL_Window* _sdlWindow;
		int _windowWidth, _windowHeight;
	};

}


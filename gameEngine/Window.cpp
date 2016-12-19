#include "Window.h"
#include "Error.h"

namespace Engine {

	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int windowWidth, int windowHeight, unsigned int flags)
	{
		Uint32 windowFlags = SDL_WINDOW_OPENGL;
		if (flags & INVISIABLE) {
			windowFlags |= SDL_WINDOW_HIDDEN;
		}
		if (flags & FULLSCREEN) {
			windowFlags |= SDL_WINDOW_FULLSCREEN;
		}
		if (flags & BORDERLESS) {
			windowFlags |= SDL_WINDOW_BORDERLESS;
		}



		_sdlWindow = SDL_CreateWindow(windowName.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			windowWidth,
			windowHeight,
			windowFlags);

		if (_sdlWindow == nullptr)
		{
			fatalError("SDL Window could not be created!");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr)
		{
			fatalError("SDL Context could not be created!");
		}

		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			fatalError("Could not initialize glew");
		}

		std::printf("*** OpenGL version: %s  ****\n", glGetString(GL_VERSION));

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//set VSYNC
		SDL_GL_SetSwapInterval(0);

		return 0;
	}

	void Window::swapWindow()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}

}

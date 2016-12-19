#include "Error.h"
#include <iostream>
#include <SDL\SDL.h>
#include <cstdlib>

namespace Engine {

	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "enter any key to exit!" << std::endl;
		int temp;
		std::cin >> temp;
		SDL_Quit();
		exit(1);
	}
}

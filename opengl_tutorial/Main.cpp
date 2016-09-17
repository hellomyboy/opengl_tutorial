#include "MainGame.h"
#include <iostream>

int main(int argc, char** argv)
{
	MainGame mainGame;
	mainGame.run();

	std::cout << "press any key to exit...";
	char a;
	std::cin >> a;

	return 0;
}
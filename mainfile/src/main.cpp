#include <iostream>

#include "Engine.h"
#include "Game.h"
#include "PathFinder.h"

int main(int argc, char* argv[])
{
	PathFinder::initialize(argv[0]);
	SceneManager engine(1920, 1080, "Test", argv[0]);
	Engine game(engine);

	game.exec();

	return 0;
}
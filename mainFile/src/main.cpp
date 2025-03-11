#include "engine.h"
#include "resourceManager.h"

int main(int argc, char* argv[])
{
    PathManager::initialize(argv[0]);

    SceneManager sceneManager(1920, 1080, "Mini-Studio");
    Engine game(sceneManager);

    game.exec();

    return 0;
}
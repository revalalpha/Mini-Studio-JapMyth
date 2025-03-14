#include "Game.h"
#include "SceneManager.h"
int main(int argc, char** argv)
{
    //Game game(argv[0]);
    //game.run();
    SceneManager test(1920, 1080,"boss", argv[0]);
    test.exec();
}

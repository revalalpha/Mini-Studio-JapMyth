#include "Game.h"
#include "SceneManager.h"



int main(int argc, char** argv)
{

    SceneManager test(1920, 1080,"Bushido no Michi", argv[0]);
    test.exec();
}

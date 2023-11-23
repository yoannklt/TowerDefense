#include "core/GameManager.h"
#include "engine/rendering/Window.h"
#include "engine/textures/TextureManager.h"
#include <iostream>
#include "./gameStates/PlayGameState.h"

int main(int argc, char** argv)
{
    std::srand(static_cast<unsigned int>(std::time(0)));

    GameManager::instance().InitGameManager(new PlayGameState());

    //GameLoop
    while (GameManager::instance().getWindow()->getSFMLObject()->isOpen())
    {
        //UPDATE
        GameManager::instance().update();

        //DISPLAY
        GameManager::instance().render();

    }

    TextureManager::destroyTexture();

    return 0;
}
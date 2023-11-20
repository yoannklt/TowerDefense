#include "core/GameManager.h"
#include "engine/rendering/Window.h"
#include "engine/textures/TextureManager.h"

int main(int argc, char** argv)
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    Window window(700, 480, "BrickBreaker");
    GameManager::bindWindow(&window);
    GameManager::InitBrickBreaker();

    //GameLoop
    while (window.getSFMLObject()->isOpen())
    {
        //UPDATE
        GameManager::update();

        //DISPLAY
        GameManager::render();

    }

    TextureManager::destroyTexture();

    return 0;
}
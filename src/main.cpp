#include "Core/Game.hpp"
#include "ECS/Systems/CollisionSystem.hpp"
#include "ECS/Tags.hpp"
#include <iostream>
#include <SDL3_image/SDL_image.h>

int main(int argc, char* argv[]) {
    Game game;

    if (game.init())
        game.run();

    ResourceManager::clearAll();
    SDL_Quit();
    game.clean();
    return 0;
}
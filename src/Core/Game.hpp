#pragma once
#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include "../ECS/Components.hpp"
#include "../Gameplay/GameScene.hpp"
#include "../ECS/Systems/MovementSystem.hpp"
#include "../ECS/Systems/EnemyAISystem.hpp"

class Game {
public:
    bool init();
    void run();
    void clean();

private:
    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    entt::registry registry;
};
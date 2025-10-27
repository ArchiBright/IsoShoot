#pragma once
#include <entt/entt.hpp>
#include "../ECS/Components.hpp"
#include "../ECS/Tags.hpp"
#include <SDL3/SDL.h>

class EnemyPool {
public:
    EnemyPool(entt::registry& registry, std::size_t poolSize = 50, SDL_Texture* texture = nullptr);

    void spawnEnemy(float x, float y);

    void update(float dt);

private:
    entt::registry& reg;
    std::vector<entt::entity> enemies;
};
#pragma once
#include <entt/entt.hpp>
#include <SDL3/SDL.h>

class EnemyAISystem {
public:
    static void update(entt::registry& reg);
};
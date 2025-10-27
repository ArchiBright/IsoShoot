#pragma once
#include <entt/entt.hpp>
#include <SDL3/SDL.h>

class MovementSystem {
public:
    static void update(entt::registry& reg, float dt);

    static void applyIntent(entt::registry& reg, float dt);

    static void apllyMovement(entt::registry& reg, float dt);
};

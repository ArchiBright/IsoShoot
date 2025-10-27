#pragma once
#include <entt/entt.hpp>
#include "../Components.hpp"
#include "../Tags.hpp"
#include <SDL3/SDL.h>

class ShootingSystem {
public:
    static void update(entt::registry& reg, float dt);
};
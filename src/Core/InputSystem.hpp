//sdl entt comoent tags
#pragma once
#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include "../ECS/Components.hpp"
#include "../ECS/Tags.hpp"

class InputSystem {
public:
    static void update(entt::registry& reg);
};
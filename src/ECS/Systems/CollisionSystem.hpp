#pragma once
#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include "../Components.hpp"

namespace CollisionSystem {
    struct Vector2f {
        float x, y;

        Vector2f(float _x = 0.f, float _y = 0.f) : x(_x), y(_y) {}
    };

    struct CollisionEvent {
         entt::registry* reg;
         entt::entity a;
         entt::entity b;
         Vector2f normal;
    };

    inline bool checkAABB(float ax, float ay, float aw, float ah,
                          float bx, float by, float bw, float bh) {
        return (ax < bx + bw && ax + aw > bx &&
                ay < by + bh && ay + ah > by);
    }

    void update(entt::registry& reg, entt::dispatcher& dispatcher);
}
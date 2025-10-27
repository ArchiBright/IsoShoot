#pragma once
#include <entt/entt.hpp>
#include "../ECS/Components.hpp"
#include "../ECS/Tags.hpp"

namespace GameplayFactory {

inline void createPlayer(entt::registry& reg, SDL_Texture* texture, float x, float y) {
        auto e = reg.create();
        reg.emplace<Position>(e, x, y);
        reg.emplace<Velocity>(e, 0.f, 0.f);
        reg.emplace<Sprite>(e, texture);
        reg.emplace<PlayerTag>(e);
        reg.emplace<InputComponent>(e);
        reg.emplace<Collider>(e, 70.f, 70.f);
        reg.emplace<MoveIntent>(e, 0.f, 0.f, 20.f);
        reg.emplace<Rotation>(e, 0.f);
    }

inline void createBackground(entt::registry& reg, SDL_Texture* texture, float x, float y) {
        auto e = reg.create();
        reg.emplace<Position>(e, x, y);
        reg.emplace<Sprite>(e, texture);
        reg.emplace<BgTag>(e);
    }
}


#pragma once
#include <entt/entt.hpp>
#include "../ECS/Components.hpp"
#include "../ECS/Tags.hpp"

namespace EnemyFactory {
inline void spawnEnemy(entt::registry& reg, SDL_Texture* texture, float x, float y) {
    auto e = reg.create();
    reg.emplace<Position>(e, x, y);
    reg.emplace<Velocity>(e, 0.f, 0.f);
    reg.emplace<Sprite>(e, texture);
    reg.emplace<EnemyTag>(e);
    reg.emplace<AIState>(e, AIState::Type::Chase);
    reg.emplace<TargetPosition>(e, x, y);
    reg.emplace<Collider>(e, 32.f, 32.f);
    reg.emplace<MoveIntent>(e, 0.f, 0.f, 100.f);
    reg.emplace<Rotation>(e, 0.f);
    reg.emplace<Health>(e, 0.f);
    }
}
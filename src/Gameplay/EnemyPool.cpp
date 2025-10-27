#include "EnemyPool.hpp"
#include <iostream>

EnemyPool::EnemyPool(entt::registry& registry, std::size_t poolSize, SDL_Texture* texture)
    : reg(registry)

{
    for (std::size_t i = 0; i < poolSize; i++) {
        enemies.reserve(poolSize);
        auto e = reg.create();
        reg.emplace<Position>(e, 0.f, 0.f);
        reg.emplace<Sprite>(e, texture);
        reg.emplace<EnemyTag>(e);
        reg.emplace<Velocity>(e, 0.f, 0.f);
        reg.emplace<Health>(e, 0.f);
        reg.emplace<AIState>(e, AIState::Type::Chase);
        reg.emplace<TargetPosition>(e, 0.f, 0.f);
        reg.emplace<Collider>(e, 60.f, 60.f);
        reg.emplace<MoveIntent>(e, 0.f, 0.f, 100.f);
        reg.emplace<Rotation>(e, 0.f);
        enemies.push_back(e);
    }
}


void EnemyPool::spawnEnemy(float x, float y) {
    for (auto e : enemies) {
        auto& health = reg.get<Health>(e);
        if (health.hp <= 0.f) {
            health.hp = 3.f;
            auto& pos = reg.get<Position>(e);

            pos.x = x;
            pos.y = y;
            return;
        }
    }
}
void EnemyPool::update(float dt) {
    // count active enemies
    int activeCount = 0;
    for (auto e : enemies) {
        auto& hp = reg.get<Health>(e);
        if (hp.hp > 0.f) activeCount++;
    }
    // respawn enemies
    if (activeCount < 15) {
        float randX = static_cast<float>(rand() % 1000);
        float randY = static_cast<float>(rand() % -30);
        spawnEnemy(randX, randY);
    }


    for (auto e : enemies) {
        auto& health = reg.get<Health>(e);
        if (health.hp <= 0.f) {
            auto& pos = reg.get<Position>(e);
            auto& vel = reg.get<Velocity>(e);
            pos.x = -500;
            pos.y = -500;
            vel.dx = vel.dy = 0;
        }
    }
}






#include "BulletPool.hpp"
#include <iostream>

BulletPool::BulletPool(entt::registry& registry, std::size_t poolSize, SDL_Texture* texture)
    : reg(registry)
{
    bullets.reserve(poolSize);
    for (std::size_t i = 0; i < poolSize; ++i) {
        auto e = reg.create();
        reg.emplace<Position>(e, -1000.f, -1000.f); // “спрятать” пулю
        reg.emplace<Velocity>(e, 0.f, 0.f);
        reg.emplace<Bullet>(e, 0.f);
        reg.emplace<BulletTag>(e);
        reg.emplace<InputComponent>(e); // если нужно
        reg.emplace<Sprite>(e, texture);
        reg.emplace<Collider>(e, 10.f, 10.f);
        reg.patch<Bullet>(e, [](Bullet& b){ b.lifetime = 0.f; });
        bullets.push_back(e);
    }
}

void BulletPool::spawnBullet(float x, float y, float dx, float dy) {
    for (auto e : bullets) {
        auto& bullet = reg.get<Bullet>(e);
        if (bullet.lifetime <= 0.f) { // найдена “спящая” пуля
            bullet.lifetime = 2.f;   // активировать
            auto& pos = reg.get<Position>(e);
            auto& vel = reg.get<Velocity>(e);

            pos.x = x;
            pos.y = y;
            vel.dx = dx;
            vel.dy = dy;
            return; // выстрел создан
        }
    }
    // Если все заняты — можно расширить пул
    // std::cout << "Bullet pool exhausted!\n";
}

void BulletPool::update(float dt) {
    for (auto e : bullets) {
        auto& bullet = reg.get<Bullet>(e);
        if (bullet.lifetime > 0.f) {
            bullet.lifetime -= dt;
            std::cout << "Bullet lifetime: " << bullet.lifetime << std::endl;
            
            if (bullet.lifetime <= 0.f) {
                // "деактивируем" пулю (прячем)
                auto& pos = reg.get<Position>(e);
                pos.x = -1000.f;
                pos.y = -1000.f;
            }
        }
    }
}
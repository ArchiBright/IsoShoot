#include "ShootingSystem.hpp"
#include "../../Core/ResourceManager.hpp"
#include <iostream>
#include "../../Gameplay/BulletPool.hpp"
#include "../../Gameplay/GameScene.hpp"


void ShootingSystem::update(entt::registry& reg, float dt) {
    auto view = reg.view<PlayerTag, Position, InputComponent, Rotation>();
    for (auto e : view) {
        auto& pos = reg.get<Position>(e);
        auto& input = reg.get<InputComponent>(e);
        auto& rot = reg.get<Rotation>(e);

        float lastShot = 0.2f;
        static float timerCooldown = 0.f;

        timerCooldown += dt;

        if (input.shoot && timerCooldown > lastShot) {
            timerCooldown = 0.f;
            float angRadiance = rot.ang * (M_PI / 180.f);
            float speed = 400.f;
            float dx = cos(angRadiance) * speed;
            float dy = sin(angRadiance) * speed;
            float playerOffset = 20.f;
            Gameplay::g_bulletPool->spawnBullet(pos.x + playerOffset, pos.y, dx, dy);
        }
    }

    // обновляем полёт пуль
    auto bullets = reg.view<Position, Velocity, Bullet>();
    for (auto entity : bullets) {
        auto& pos = bullets.get<Position>(entity);
        auto& vel = bullets.get<Velocity>(entity);

        pos.x += vel.dx * (1.0f / 60.0f); // фиктивный dt
        pos.y += vel.dy * (1.0f / 60.0f);
    }
}
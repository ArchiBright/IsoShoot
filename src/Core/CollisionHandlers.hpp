#include "../ECS/Systems/CollisionSystem.hpp"
#include "../ECS/Tags.hpp"
#include <iostream>
#include "entt/entt.hpp"

inline void handleCollisions(CollisionSystem::CollisionEvent e) {
    auto& reg = *e.reg;

    if (reg.any_of<Velocity>(e.a)) {
        auto& velA = reg.get<Velocity>(e.a);
        float dotA = velA.dx * e.normal.x + velA.dy * e.normal.y;
        if (dotA < 0.f) { // объект врезается в препятствие
            velA.dx -= dotA * e.normal.x;
            velA.dy -= dotA * e.normal.y;
        }
    }

    if (reg.any_of<Velocity>(e.b)) {
        auto& velB = reg.get<Velocity>(e.b);
        float dotB = velB.dx * (-e.normal.x) + velB.dy * (-e.normal.y);
        if (dotB < 0.f) {
            velB.dx -= dotB * (-e.normal.x);
            velB.dy -= dotB * (-e.normal.y);
        }
    }

    if ((reg.any_of<BulletTag>(e.a) && reg.any_of<EnemyTag>(e.b)) ||
        (reg.any_of<EnemyTag>(e.a) && reg.any_of<BulletTag>(e.b))) {
        auto enemy = reg.any_of<EnemyTag>(e.a) ? e.a : e.b;
        auto bullet = reg.any_of<BulletTag>(e.a) ? e.a : e.b;
        auto& bullethp = reg.get<Bullet>(bullet);
        auto& bulletPos = reg.get<Position>(bullet);
        // auto& hitFlash = reg.get<HitFlash>(enemy);


        if (!reg.all_of<HitFlash>(enemy)) {
            reg.emplace_or_replace<HitFlash>(enemy, HitFlash{0.1f});
        }
        
        // reg.patch<HitFlash>(enemy, [](HitFlash& flash){flash.timer = 0.2f;});
        reg.patch<Bullet>(bullet, [](Bullet& life){life.lifetime = 0.f;});
        reg.patch<Health>(enemy, [](Health& h){h.hp -= 1.f;});

        bulletPos.x = -1000;
        bulletPos.y = -1000;
        
    }
}




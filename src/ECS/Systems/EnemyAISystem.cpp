#pragma once
#include "EnemyAISystem.hpp"
#include "../Components.hpp"
#include "../Tags.hpp"

void EnemyAISystem::update(entt::registry& reg) {
    // player position

    auto playerView = reg.view<Position, PlayerTag>();
    Position playerPos{};
    for (auto [player, pos] : playerView.each()) {
        playerPos = pos;
    }

    // enemy's target detection
    auto enemyViews = reg.view<Position, TargetPosition, AIState, MoveIntent, Rotation>(); // берем все сущности с данными компонентами
    for (auto [enemy, pos, target, ai, intent, rot] : enemyViews.each()) { // проходимся циклом
        float dx = playerPos.x - pos.x; // вычисляем расстояния каждой оси
        float dy = playerPos.y - pos.y;
        float distance = std::hypot(dx, dy); // через теорему пифагора находим гипотенузу расстояние
        float agroDistance = 2000.f; // устанавливаем минимальную дистанцию агра
        float angle = atan2(dy, dx);
        double rotDeeg = angle * 180 / M_PI;
        

        if (distance < agroDistance && distance > 0.00001f)
            ai.state = AIState::Chase;
        else
            ai.state = AIState::Idle;

        if (ai.state == AIState::Chase) {
            rot.ang = rotDeeg;
            // distance normalized
            dx /= distance;
            dy /= distance;
            intent.dx = dx;
            intent.dy = dy;
        }
    }
}

// Даем доступ к клавиатуре пишем в нее нулевой адрес просто создаем коробку
// дальше работаем с ентт
// берем в кулак все сущности с ускорением и позицией
// начинаем цикл (цикл - основа ECS системы)

// СБРАСЫВАЕМ СКОРОСТЬ ПЕРЕД НАЧАЛО КЖДОГО КАДРА
// в цикле берем все что с ускорением и все что с позицией
// стаавим условия - если клавиша нажата - изменить позицию
// в конце кода передвигаем обхект физически умножая значение изменения (скорость)
// на дельту времени для плавности при любом фпс

#include "MovementSystem.hpp"
#include "../Components.hpp"  // Здесь Position и Velocity
#include "../Tags.hpp"
#include <iostream>

void MovementSystem::applyIntent(entt::registry& reg, float dt) {

    auto intentView = reg.view<Position, Velocity, MoveIntent>(); // берем нужные нам представления

    for (auto entity : intentView) { // проходимся по ним циклом
        auto& pos = intentView.get<Position>(entity);
        auto& vel = intentView.get<Velocity>(entity);
        auto& intent = intentView.get<MoveIntent>(entity);

        vel.dx = intent.dx * intent.speed;
        vel.dy = intent.dy * intent.speed;

    }
}

void MovementSystem::apllyMovement(entt::registry& reg, float dt) {

    auto moveView = reg.view<Position, Velocity>();

    for (auto e : moveView) {
        auto& pos = reg.get<Position>(e);
        auto& vel = reg.get<Velocity>(e);

        pos.x += vel.dx * dt;
        pos.y += vel.dy * dt;
    }
}
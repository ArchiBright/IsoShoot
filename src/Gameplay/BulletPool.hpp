#pragma once
#include <entt/entt.hpp>
#include "../ECS/Components.hpp"
#include "../ECS/Tags.hpp"
#include <SDL3/SDL.h>

// BulletPool отвечает за:
// 1. Хранение заранее созданных пуль (вектор entity)
// 2. Активацию / деактивацию пуль
// 3. Перезапуск позиции и таймера жизни

class BulletPool {
public:
    BulletPool(entt::registry& registry, std::size_t poolSize = 20, SDL_Texture* texture = nullptr);

    // активирует пулю и устанавливает позицию
    void spawnBullet(float x, float y, float dx, float dy);

    // обновляет таймер жизни и деактивирует старые пули
    void update(float dt);

private:
    entt::registry& reg;
    std::vector<entt::entity> bullets;
};
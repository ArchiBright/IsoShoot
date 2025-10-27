#pragma once
#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include "../ECS/Systems/CollisionSystem.hpp"
#include "../ECS/Components.hpp"
#include "GameplayFactory.hpp"
#include "EnemyFactory.hpp"
#include "BulletPool.hpp"
#include "../Core/InputSystem.hpp"
#include "../ECS/Tags.hpp"
#include "../ECS/Systems/MovementSystem.hpp"
#include "../ECS/Systems/EnemyAISystem.hpp"
#include "../Core/ResourceManager.hpp"
#include "../ECS/Systems/ShootingSystem.hpp"
#include "../Core/CollisionHandlers.hpp"
#include "EnemyPool.hpp"
#include "../ECS/Systems/DmgFeedbackSYS.hpp"

namespace Gameplay {

inline BulletPool* g_bulletPool = nullptr; // ✅ теперь общедоступная переменная
inline EnemyPool* g_enemyPool = nullptr;
inline entt::dispatcher g_dispatcher;


inline void initGameScene(entt::registry& reg, SDL_Renderer* renderer) {
    SDL_Texture* playerText = ResourceManager::loadTexture(renderer, "player", "../src/assets/textures/playerShip.png");
    SDL_Texture* enemyText  = ResourceManager::loadTexture(renderer, "enemy", "../src/assets/textures/enemyShip.png");
    SDL_Texture* bulletText = ResourceManager::loadTexture(renderer, "bullet", "../src/assets/textures/bullet.png");
    SDL_Texture* bgTexture = ResourceManager::loadTexture(renderer, "background", "../src/assets/textures/bgTexture.png");
    // SDL_Texture* dockWallText = ResourceManager::loadTexture(renderer, "wall", "../src/assets/textures/dockWall.png");
    GameplayFactory::createBackground(reg, bgTexture, 0.f, 0.f);
    g_bulletPool = new BulletPool(reg, 50, bulletText);
    g_enemyPool = new EnemyPool(reg, 20, enemyText);
    g_dispatcher.sink<CollisionSystem::CollisionEvent>().connect<&handleCollisions>();

    GameplayFactory::createPlayer(reg, playerText, 100.f, 300.f);
    


    // spawn enemies
    float startX = 200.f;
    for (int i = 0; i < 20; i++) {
        float currentX = startX + (i * 100.f);
        g_enemyPool->spawnEnemy(currentX, -100.f);
    }
}

inline void updateGameScene(entt::registry& reg, float dt) {
    InputSystem::update(reg);
    EnemyAISystem::update(reg);
    ShootingSystem::update(reg, dt);
    DamageFeedback::hitFlash(reg, dt);
    MovementSystem::applyIntent(reg, dt);
    if (g_bulletPool) g_bulletPool->update(dt);
    if (g_enemyPool) g_enemyPool->update(dt);
    CollisionSystem::update(reg, g_dispatcher);
    MovementSystem::apllyMovement(reg, dt);
}

inline void renderGameScene(entt::registry& reg, SDL_Renderer* renderer) {
    auto playerView = reg.view<Position, Sprite, PlayerTag, Collider, Rotation>();
    auto enemyView  = reg.view<Position, Sprite, EnemyTag, Collider, Rotation>();
    auto bulletView = reg.view<Position, Sprite, BulletTag>();
    auto bgView = reg.view<Position, Sprite, BgTag>();

    for (auto [e, pos, sprite] : bgView.each()) {
        SDL_FRect dst = {pos.x, pos.y, 1000.f, 800.f};
        SDL_RenderTextureRotated(renderer, sprite.texture, nullptr, &dst, 0.f, nullptr, SDL_FLIP_NONE);
    }

    for (auto [e, pos, sprite, col, rot] : playerView.each()) {
        SDL_FRect dst = {pos.x, pos.y, col.width, col.height};
        SDL_RenderTextureRotated(renderer, sprite.texture, nullptr, &dst, rot.ang + 90.f, nullptr, SDL_FLIP_NONE);
    }
    for (auto [e, pos, sprite, col, rot] : enemyView.each()) {
        SDL_SetTextureColorMod(sprite.texture, sprite.tint.r, sprite.tint.g, sprite.tint.b);
        SDL_FRect dst = {pos.x, pos.y, col.width, col.height};
        SDL_RenderTextureRotated(renderer, sprite.texture, nullptr, &dst, rot.ang + 90.f, nullptr, SDL_FLIP_NONE);
    }
    for (auto [e, pos, sprite] : bulletView.each()) {
        SDL_FRect dst = {pos.x, pos.y, 20.f, 20.f};
        SDL_RenderTexture(renderer, sprite.texture, nullptr, &dst);
    }
    
}
}
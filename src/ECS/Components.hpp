#pragma once
#include <SDL3/SDL.h>

struct Position {
    float x, y;
};

struct Rotation {
    double ang;
};

struct MoveIntent {
    float dx, dy = 0.f;
    float speed = 0.f;
};

struct Velocity {
    float dx, dy;
};

struct Sprite {
    SDL_Texture* texture;
    SDL_Color tint = {255, 255, 255};
};

struct TargetPosition {
    float x, y;
};

struct AIState {
    enum Type {
        Idle,
        Chase
    } state = Chase;
};

struct Bullet {
    float lifetime =  2.f;
};

struct InputComponent {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;
};

struct Collider {
    float width;
    float height;
    bool isTriggered = false;
};

struct Health {
    float hp = 1.f;
};

struct HitFlash {
    float timer;
};
#include "InputSystem.hpp"
#include <SDL3/SDL_mouse.h>
#include <iostream>
#include <SDL3/SDL.h>

void InputSystem::update(entt::registry& reg) {
    float mouseX = 0.0f;
    float mouseY = 0.0f;
    SDL_MouseButtonFlags mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    bool leftPressed = mouseState & SDL_BUTTON_LMASK;
    
    auto rotView = reg.view<Rotation, Position, PlayerTag>();
    for (auto e : rotView) {
        auto& rot = reg.get<Rotation>(e);
        auto& pos = reg.get<Position>(e);

        // находим катеты
        float distX = mouseX - pos.x;
        float distY = mouseY - pos.y;
        float angle = atan2(distY, distX);
        double rotDeeg = angle * 180 / M_PI;
        rot.ang = rotDeeg;
    }

    const bool* state = SDL_GetKeyboardState(nullptr);


    auto view = reg.view<InputComponent, MoveIntent, PlayerTag, Sprite>();
    for (auto entity : view) {
        auto& input = view.get<InputComponent>(entity);
        auto& intent = view.get<MoveIntent>(entity);
        auto& text = view.get<Sprite>(entity);

        input.left  = state[SDL_SCANCODE_A];
        input.right = state[SDL_SCANCODE_D];
        input.up    = state[SDL_SCANCODE_W];
        input.down  = state[SDL_SCANCODE_S];
        input.shoot = state[SDL_SCANCODE_SPACE]|| leftPressed;

        intent.dx = 0.f;
        intent.dy = 0.f;
        intent.speed = 200.f;

        if (input.left) intent.dx = -1.f; // байндим клавиши
        if (input.right) intent.dx = 1.f;
        if (input.up) intent.dy = -1.f;
        if (input.down) intent.dy = 1.f;

        float len = std::hypot(intent.dx, intent.dy);
        if (len > 0){
            intent.dx /= len;
            intent.dy /= len;
        } else {
            intent.speed = 0.f;
        }
    }
}
#pragma once
#include <iostream>
#include <entt/entt.hpp>
#include <SDL3/SDL.h>


namespace DamageFeedback {
    inline void hitFlash(entt::registry& reg, float dt) {
        auto view = reg.view<HitFlash, Sprite>();
        for (auto e : view) {
            auto& flash = reg.get<HitFlash>(e);
            auto& text = reg.get<Sprite>(e);
            if (flash.timer > 0.f) {
                text.tint.r = 255;
                text.tint.g = 120;
                text.tint.b = 120; // тёплый красно-белый флэш
                flash.timer -= dt;
            }
            if (flash.timer <= 0) {
                text.tint.r = 255;
                text.tint.g = 255;
                text.tint.b = 255;
                reg.remove<HitFlash>(e);
            }
        }
    }
}
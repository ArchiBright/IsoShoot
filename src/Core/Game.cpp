#include "Game.hpp"
#include <iostream>
#include "../Gameplay/BulletPool.hpp"

// в этом файле мы запускаем игру. Мы инициализируем игру (запускаем машину) создаем окно, создаем рендер
// и даем статус флага игра активна
// инициализируем видео здесь
bool Game::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL init failed!" << SDL_GetError() << std::endl;
        return false;
    }

// создаем окно с проверкой
    window = SDL_CreateWindow("IsoShoot", 1000, 800, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }


// создаем кисть - рендерер
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // воспроизводим игровую сцену

    Gameplay::initGameScene(registry, renderer);
    isRunning = true;
    return true;
}


// здесь мы нажимаем педаль газа в игре, то есть запускаем окно, и запускаем видеофабрику
// видеофабрика: обновить данные - дать краску - залить холст - нарисовать в бекбуффер - 
// поменять бек-с-фронт

void Game::run() {
        Uint64 lastTime = SDL_GetTicks();
        SDL_Event e;
        while (isRunning) {
            while(SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT)
                isRunning = false;
            }
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        Gameplay::updateGameScene(registry, deltaTime); // update game scene - logic and calculations, no drawing

        // Renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fill the screen of back buffer with this color
        SDL_RenderClear(renderer); // clear the back-buffer window before drawing new updated scene
        Gameplay::renderGameScene(registry, renderer); // render new updated scene to back buffer
        SDL_RenderPresent(renderer); // swap buffers
        }
    }

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

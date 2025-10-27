#pragma once
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class ResourceManager {
public:
    static SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& name, const std::string& path);
    static SDL_Texture* getTexture(const std::string& name);
    static void clearAll();

private:
    static std::unordered_map<std::string, SDL_Texture*> textures;
};
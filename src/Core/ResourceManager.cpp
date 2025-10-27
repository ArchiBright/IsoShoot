#include "ResourceManager.hpp"
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> ResourceManager::textures;

SDL_Texture* ResourceManager::loadTexture(SDL_Renderer* renderer, const std::string& name, const std::string& path)
{
    // Проверка кэша
    if (textures.contains(name))
        return textures[name];

    SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
    if (!tex) {
        std::cerr << "❌ Ошибка загрузки текстуры '" << name << "' из " << path
                  <<  std::endl;
        return nullptr;
    }

    textures[name] = tex;
    std::cout << "✅ Текстура загружена: " << name << " (" << path << ")\n";
    return tex;
}

SDL_Texture* ResourceManager::getTexture(const std::string& name)
{
    if (!textures.contains(name)) {
        std::cerr << "⚠️ Текстура не найдена: " << name << std::endl;
        return nullptr;
    }
    return textures[name];
}

void ResourceManager::clearAll()
{
    for (auto& [key, tex] : textures) {
        SDL_DestroyTexture(tex);
    }
    textures.clear();
    std::cout << "🧹 Все текстуры очищены\n";
}
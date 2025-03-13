#include "TextureManager.hpp"

std::unordered_map<std::string, sf::Texture> TextureManager::textures;
sf::Texture &TextureManager::getTexture(const std::string &path)
{
    auto it = textures.find(path);
    if(it == textures.end())
    {
        sf::Texture texture;

        if(!texture.loadFromFile(path))
        {
            throw std::runtime_error("Failed to load texture: " + path);
        }

        auto [newIt, _] = textures.insert({path, std::move(texture)});
        return newIt->second;
    }

    return it->second;
}

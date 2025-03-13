#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

namespace TextureManager
{
    static std::unordered_map<std::string, sf::Texture> textures;
    sf::Texture &getTexture(const std::string &path);
} // namespace TextureManager

#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <map>

namespace TextureManager
{
    extern std::map<std::string, sf::Texture> textures;
    sf::Texture &getTexture(const std::string &path);
} // namespace TextureManager

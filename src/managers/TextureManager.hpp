#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace TextureManager
{
    sf::Texture &getTexture(const std::string &path);
} // namespace TextureManager

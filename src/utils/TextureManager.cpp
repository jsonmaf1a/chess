#include "TextureManager.hpp"

namespace TextureManager
{
    std::unordered_map<std::string, sf::Texture> textures;

    sf::Texture &getTexture(const std::string &path)
    {
        auto it = textures.find(path);
        if(it == textures.end())
        {
            sf::Texture texture;
            texture.setSmooth(false);

            if(!texture.loadFromFile(path))
            {
                throw std::runtime_error("Failed to load texture: " + path);
            }

            auto [newIt, _] = textures.insert({path, std::move(texture)});
            return newIt->second;
        }

        return it->second;
    }
} // namespace TextureManager

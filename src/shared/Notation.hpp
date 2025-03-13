#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>

namespace Notation
{
    std::string toChessNotation(const sf::Vector2i &pos);
    sf::Vector2i fromChessNotation(const std::string &notation);

} // namespace Notation

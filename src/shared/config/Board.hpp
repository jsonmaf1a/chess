#pragma once

#include "Layout.hpp"

namespace BoardConfig
{
    static constexpr int GridSize = 8;
    static constexpr float CellSize =
        LayoutConfig::BoardBounds.size.x / GridSize;

} // namespace BoardConfig

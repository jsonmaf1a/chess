#pragma once

#include <string_view>

namespace StringUtils
{
    template <typename T> constexpr std::string_view stringify(T);
}

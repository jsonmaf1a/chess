#include "managers/ThemeManager.hpp"
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <unordered_map>

namespace
{
    static const std::string BASE_PATH = "./assets/themes/";

    static std::unordered_map<ThemeID, Theme> themes;
    static std::unordered_map<ThemeID, std::string> themePaths = {
        {ThemeID::Default, BASE_PATH + "default.ini"},
        {ThemeID::Neon, BASE_PATH + "neon.ini"}};

    static ThemeID currentTheme = ThemeID::Default;
} // namespace

namespace ThemeManager
{
    Theme getTheme() { return themes.at(currentTheme); }
    void setTheme(ThemeID id) { currentTheme = id; }

    void loadThemes()
    {
        for(const auto [id, path] : themePaths)
        {
            themes.insert({id, loadTheme(path)});
        }
    }

    Theme loadTheme(const std::string &filename)
    {
        Theme theme;
        std::ifstream file(filename);
        if(!file)
        {
            std::cerr << "Failed to open theme file: " << filename << std::endl;
            return theme;
        }

        std::unordered_map<std::string, std::string> values;
        std::string line, section;

        while(std::getline(file, line))
        {
            line = line.substr(0, line.find(';'));
            if(line.empty())
                continue;

            if(line.front() == '[' && line.back() == ']')
            {
                section = line.substr(1, line.size() - 2);
            }
            else
            {
                std::istringstream ss(line);
                std::string key, value;
                if(std::getline(ss, key, '=') && std::getline(ss, value))
                {
                    key.erase(0, key.find_first_not_of(" \t"));
                    key.erase(key.find_last_not_of(" \t") + 1);

                    value.erase(0, value.find_first_not_of(" \t"));
                    value.erase(value.find_last_not_of(" \t") + 1);

                    values[section + "." + key] = value;
                }
            }
        }

        theme.ui.background = parseColor(values["ui.background"]);
        theme.ui.foreground = parseColor(values["ui.foreground"]);
        theme.ui.foregroundDark = parseColor(values["ui.foregroundDark"]);
        theme.ui.accent = parseColor(values["ui.accent"]);
        theme.ui.highlight = parseColor(values["ui.highlight"]);
        theme.ui.shadow = parseColor(values["ui.shadow"]);

        theme.board.light = parseColor(values["board.light"]);
        theme.board.dark = parseColor(values["board.dark"]);
        theme.board.hovered = parseColor(values["board.hovered"]);
        theme.board.highlighted = parseColor(values["board.highlighted"]);
        theme.board.selected = parseColor(values["board.selected"]);

        return theme;
    }

    const sf::Color parseColor(const std::string &hex)
    {
        unsigned int r, g, b, a = 255;

        if(hex.length() == 9)
        {
            sscanf(hex.c_str(), "#%02x%02x%02x%02x", &r, &g, &b, &a);
        }
        else if(hex.length() == 7)
        {
            sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
        }
        else if(hex.length() == 4)
        {
            unsigned int rr, gg, bb;
            sscanf(hex.c_str(), "#%1x%1x%1x", &rr, &gg, &bb);
            r = rr * 17;
            g = gg * 17;
            b = bb * 17;
        }

        else
        {
            std::cerr << "Failed to parse HEX color: " << hex.c_str()
                      << ".\t Using BLACK\n";
            return sf::Color(0, 0, 0, 255);
        }

        return sf::Color(r, g, b, a);
    }
} // namespace ThemeManager

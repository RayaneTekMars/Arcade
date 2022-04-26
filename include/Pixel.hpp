/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Pixel
*/

#pragma once

#include <string>

namespace Arcade
{
    /**
     * @class Color
     * @brief Color struct
     */
    struct Color
    {
        public:

            unsigned char r, g, b, a;
    };

    /**
     * @class Pixel
     * @brief Pixel struct
     */
    struct Pixel
    {
        public:

            Color c;
            std::string s;
            bool m;
    };
} // namespace Arcade
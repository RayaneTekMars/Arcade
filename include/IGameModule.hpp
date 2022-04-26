/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** IGameModule
*/

#pragma once

#include "KeyboardInput.hpp"
#include "ModuleType.hpp"
#include "Pixel.hpp"
#include "Title.hpp"

#include <map>
#include <string>
#include <vector>

namespace Arcade
{
    class IGameModule
    {
        public:

            enum GameState { Playing, Won, Lost };

        public:

            virtual ~IGameModule() = default;

            virtual void init() = 0;
            virtual void frame(KeyboardInput input) = 0;

            virtual void setScores(const std::string &username, size_t score) = 0;

            virtual GameState getState() = 0;
            virtual std::size_t getLives() = 0;
            virtual std::size_t getScore() = 0;
            virtual const Title &getTitle() = 0;
            virtual const std::string &getName() = 0;
            virtual const std::vector<std::string> &getMap() = 0;
            virtual const std::map<char, Pixel> &getSubPixel() = 0;
            virtual const std::map<std::string, std::size_t> &getScores() = 0;

        protected:

            virtual void loadMap(const std::string &filename) = 0;
            virtual void loadScores(const std::string &filename) = 0;
            virtual void saveScores(const std::string &filename) = 0;
            virtual void loadTitle(const std::string &image, const std::string &ascii) = 0;
    };
} // namespace Arcade

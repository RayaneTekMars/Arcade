/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** AGameModule
*/

#pragma once

#include "IGameModule.hpp"

#include <iostream>
#include <fstream>
#include <regex>

namespace Arcade
{
    class AGameModule : IGameModule
    {
        public:

            ~AGameModule() override;

            void init() override;
            void frame(KeyboardInput input) override;

            void setScores(const std::string &username, size_t score) final;

            GameState getState() final;
            std::size_t getLives() final;
            std::size_t getScore() final;
            const Title &getTitle() final;
            const std::string &getName() final;
            const std::map<char, Pixel> &getSubPixel() final;
            const std::vector<std::string> &getMap() override;
            const std::map<std::string, std::size_t> &getScores() final;

        protected:

            AGameModule(const std::string &name);

            void loadMap(const std::string &filename) final;
            void loadScores(const std::string &filename) final;
            void saveScores(const std::string &filename) final;
            void loadTitle(const std::string &image, const std::string &ascii) final;

            Title m_title;
            GameState m_state;
            std::string m_name;
            std::size_t m_score;
            std::size_t m_lives;
            std::vector<std::string> m_map;
            std::map<char, Pixel> m_subPixel;
            std::map<std::string, std::size_t> m_leaderBoard;
    };
} // namespace Arcade
/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** ADisplayModule
*/

#pragma once

#include "IDisplayModule.hpp"

namespace Arcade
{
    class ADisplayModule : public IDisplayModule
    {
        public:

            ~ADisplayModule() override;

            void init() override;
            void initGame(const Title &title, const std::map<char, Pixel> &subPixel) override;

            void stop() override;

            bool displayMainMenu(const Arcade::KeyboardInput &key,
                const std::vector<Arcade::IDisplayModule *> &libs,
                const std::vector<Arcade::IGameModule *> &games, std::string &username,
                int &choice) override;
            void displayGame(const std::vector<std::string> &map,
                const std::map<std::string, std::size_t> &scores, std::size_t score,
                std::size_t lives) override;
            void displayVictory(const std::string username, std::size_t scores) override;
            void displayGameover(const std::string username, std::size_t scores) override;

            const std::string &getName() final;
            KeyboardInput getInput() override;

        protected:

            ADisplayModule(const std::string &name);

            std::string m_name;
            std::map<char, Pixel> m_subPixel, m_gamePixel;
            Title m_title, m_arcade, m_gameover, m_victory;
    };
} // namespace Arcade
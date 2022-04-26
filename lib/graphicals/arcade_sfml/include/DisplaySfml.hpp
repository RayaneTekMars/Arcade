/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Espace de travail)
** File description:
** DisplaySfml
*/

#pragma once

#include "ADisplayModule.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class DisplaySfml : Arcade::ADisplayModule
{
    public:

        DisplaySfml();
        ~DisplaySfml();

        void init() final;
        void initGame(const Title &title, const std::map<char, Arcade::Pixel> &subPixel) final;

        void stop() final;

        bool displayMainMenu(const Arcade::KeyboardInput &key,
            const std::vector<Arcade::IDisplayModule *> &libs,
            const std::vector<Arcade::IGameModule *> &games, std::string &username,
            int &choice) final;
        void displayGame(const std::vector<std::string> &map,
            const std::map<std::string, std::size_t> &scores, std::size_t score,
            std::size_t lives) final;
        void displayVictory(const std::string username, std::size_t scores) final;
        void displayGameover(const std::string username, std::size_t scores) final;

        Arcade::KeyboardInput getInput() final;

    private:

        bool m_enter;

        static sf::Font m_font;
        static sf::Text m_text;
        static sf::Sprite m_sprite;
        static sf::Texture m_texture;
        sf::RenderWindow *m_window;
        sf::RectangleShape m_rectangle;
        sf::CircleShape m_circle;
};

void loadDisplaySfml() __attribute__((constructor));

void unloadDisplaySfml() __attribute__((destructor));

extern "C" DisplaySfml *entryPoint();

extern "C" Arcade::ModuleType getType();
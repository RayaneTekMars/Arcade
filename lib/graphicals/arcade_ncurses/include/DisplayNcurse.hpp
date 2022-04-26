/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** DisplayNcurse
*/

#pragma once

#include "ADisplayModule.hpp"

#include <curses.h>
#include <locale.h>

class DisplayNcurse : Arcade::ADisplayModule
{
    public:

        DisplayNcurse();
        ~DisplayNcurse() final;

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
};

void loadDisplayNcurse() __attribute__((constructor));

void unloadDisplayNcurse() __attribute__((destructor));

extern "C" DisplayNcurse *entryPoint();

extern "C" Arcade::ModuleType getType();
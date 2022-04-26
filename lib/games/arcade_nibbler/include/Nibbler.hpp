/*
** EPITECH PROJECT, 2022
** Nibbler.hpp
** File description:
** Nibbler.hpp
*/

#pragma once

#include "AGameModule.hpp"

#include <cstdlib>
#include <ctime>
#include <functional>
#include <map>
#include <utility>

class Nibbler : public Arcade::AGameModule
{
    public:

        enum direction {
            TOP,
            BOTTOM,
            LEFT,
            RIGHT,
        };

    public:

        Nibbler();
        ~Nibbler();

        void init() override;
        void frame(Arcade::KeyboardInput input) final;

        const std::vector<std::string> &getMap() final;

    private:

        void victory();
        bool bodyContact(int i, int y);
        void spawnFood();

        direction m_direction = RIGHT;
        std::vector<std::string> m_mapTmp;
        std::vector<std::pair<int, int>> m_coord;
};

void loadNibbler() __attribute__((constructor));

void unloadNibbler() __attribute__((destructor));

extern "C" Nibbler *entryPoint();

extern "C" Arcade::ModuleType getType();

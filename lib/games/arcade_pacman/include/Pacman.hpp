/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** Pacman
*/

#pragma once

#include "AGameModule.hpp"
#include "KeyboardInput.hpp"

class Pacman : public Arcade::AGameModule
{
    public:

        Pacman();
        ~Pacman();

        enum Direction { UP, DOWN, LEFT, RIGHT, NONE };

        struct GhostsInfos
        {
            public:

                int x;
                int y;
                char name;
        };

        struct PacmanInfos
        {
            public:

                int x;
                int y;
                char name;
        };

        void init() final;
        void frame(Arcade::KeyboardInput input) final;
        const std::vector<std::string> &getMap() final;
        void GhostMove();
        void PacmanEat();
        void PacmanMove();
        void PacmanLoseLife();
        void PacmanWin();

    protected:

    private:

        std::vector<std::string> m_mapTmp;

        PacmanInfos m_pacman;
        std::vector<GhostsInfos> m_ghosts;
        Direction m_direction = NONE;
};

void loadPacman() __attribute__((constructor));

void unloadPacman() __attribute__((destructor));

extern "C" Pacman *entryPoint();

extern "C" Arcade::ModuleType getType();

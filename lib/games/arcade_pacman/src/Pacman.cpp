/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** Pacman
*/

#include "../include/Pacman.hpp"

Arcade::ModuleType type = Arcade::ModuleType::Game;

Pacman *instance = nullptr;

Pacman::Pacman() : Arcade::AGameModule("Pacman")
{
    m_subPixel = {
        // TITLE PIXEL
        {'_', {{0, 0, 0, 0}, " ", false}},
        {'X', {{0, 0, 0, 0}, "█", false}},
        {'|', {{0, 0, 0, 0}, "║", false}},
        {'-', {{0, 0, 0, 0}, "═", false}},
        {'J', {{0, 0, 0, 0}, "╝", false}},
        {'L', {{0, 0, 0, 0}, "╚", false}},
        {'/', {{0, 0, 0, 0}, "╔", false}},
        {'\\', {{0, 0, 0, 0}, "╗", false}},
        // GAME PIXEL
        {'#', {{0, 0, 0, 255}, "🟦", false}},
        {'D', {{0, 0, 0, 255}, "🟥", false}},
        {' ', {{125, 125, 125, 150}, "⬛", false}},
        {'x', {{0, 0, 255, 100}, "🟪", false}},
        {'F', {{255, 0, 0, 255}, "🔴", false}},
        {'P', {{255, 255, 0, 255}, "😶", false}},
        {'R', {{255, 0, 0, 255}, "👿", true}},
        {'G', {{0, 255, 0, 255}, "👹", true}},
        {'B', {{0, 0, 255, 255}, "👺", true}},
        {'Y', {{255, 255, 0, 255}, "🤡", true}}
    };
    loadTitle("./lib/games/arcade_pacman/assets/title/image.png",
        "./lib/games/arcade_pacman/assets/title/ascii.txt");
    loadScores("./lib/games/arcade_pacman/data/scores.txt");
    init();
}

Pacman::~Pacman() { saveScores("./lib/games/arcade_pacman/data/scores.txt"); }

void Pacman::init()
{
    loadMap("./lib/games/arcade_pacman/assets/map/map.txt");
    m_ghosts = {
        {17, 16, 'R'},
        {18, 16, 'G'},
        {20, 16, 'B'},
        {21, 16, 'Y'}
    };
    m_pacman = {19, 19, 'P'};
    m_lives = 3;
    m_score = 0;
    m_state = Arcade::IGameModule::Playing;
    m_direction = NONE;
}

void Pacman::frame(Arcade::KeyboardInput input)
{
    switch (input.key) {
        case Arcade::KeyboardInput::Key::Z:
            m_direction = UP;
            break;
        case Arcade::KeyboardInput::Key::Q:
            m_direction = LEFT;
            break;
        case Arcade::KeyboardInput::Key::S:
            m_direction = DOWN;
            break;
        case Arcade::KeyboardInput::Key::D:
            m_direction = RIGHT;
            break;
    }
    PacmanMove();
    PacmanEat();
    PacmanLoseLife();
    GhostMove();
    PacmanWin();
}

void Pacman::PacmanEat()
{
    if (m_map[m_pacman.y][m_pacman.x] == 'x')
        m_score += 10;
    else if (m_map[m_pacman.y][m_pacman.x] == 'F')
        m_score += 50;
    m_map[m_pacman.y][m_pacman.x] = ' ';
}

void Pacman::PacmanWin()
{
    if (m_lives > 0 && m_state == Arcade::IGameModule::Playing) {
        for (int i = 0; i < m_map.size(); i++)
            for (int j = 0; j < m_map[i].size(); j++)
                if (m_map[i][j] == 'x')
                    return;
        m_state = Arcade::IGameModule::Won;
    }
}

void Pacman::PacmanMove()
{
    if (m_direction == UP) {
        if (m_map[m_pacman.y - 1][m_pacman.x] == ' ' || m_map[m_pacman.y - 1][m_pacman.x] == 'x'
            || m_map[m_pacman.y - 1][m_pacman.x] == 'F') {
            m_pacman.y--;
        }
    }
    if (m_direction == DOWN) {
        if (m_map[m_pacman.y + 1][m_pacman.x] == ' ' || m_map[m_pacman.y + 1][m_pacman.x] == 'x'
            || m_map[m_pacman.y + 1][m_pacman.x] == 'F') {
            m_pacman.y++;
        }
    }
    if (m_direction == LEFT) {
        if (m_map[m_pacman.y][m_pacman.x - 1] == ' ' || m_map[m_pacman.y][m_pacman.x - 1] == 'x'
            || m_map[m_pacman.y][m_pacman.x - 1] == 'F') {
            m_pacman.x--;
        }
    }
    if (m_direction == RIGHT) {
        if (m_map[m_pacman.y][m_pacman.x + 1] == ' ' || m_map[m_pacman.y][m_pacman.x + 1] == 'x'
            || m_map[m_pacman.y][m_pacman.x + 1] == 'F') {
            m_pacman.x++;
        }
    }
}

void Pacman::GhostMove()
{
    for (auto &ghost : m_ghosts) {
        int x = ghost.x;
        int y = ghost.y;
        int direction = rand() % 4;
        if (direction == 0 && m_map[y - 1][x] != '#')
            ghost.y--;
        else if (direction == 1 && m_map[y + 1][x] != '#')
            ghost.y++;
        else if (direction == 2 && m_map[y][x - 1] != '#')
            ghost.x--;
        else if (direction == 3 && m_map[y][x + 1] != '#')
            ghost.x++;
    }
}

void Pacman::PacmanLoseLife()
{
    int x = 18;

    for (std::size_t i = 0; i < m_ghosts.size(); i++) {
        if (m_pacman.y == m_ghosts[i].y && m_pacman.x == m_ghosts[i].x) {
            if (m_lives > 1) {
                m_lives--;
                for (std::size_t j = 0; j < m_ghosts.size(); j++)
                    m_ghosts[j] = {.x = x++, .y = 16, .name = m_ghosts[j].name};
                m_pacman = {.x = 19, .y = 19, .name = m_pacman.name};
                m_direction = NONE;
            } else {
                m_state = Arcade::IGameModule::Lost;
            }
            break;
        }
    }
}

const std::vector<std::string> &Pacman::getMap()
{
    m_mapTmp.assign(m_map.begin(), m_map.end());

    for (std::size_t i = 0; i < m_ghosts.size(); i++)
        m_mapTmp[m_ghosts[i].y][m_ghosts[i].x] = m_ghosts[i].name;
    m_mapTmp[m_pacman.y][m_pacman.x] = m_pacman.name;
    return (m_mapTmp);
}

void loadPacman() { instance = new Pacman; }

void unloadPacman() { delete instance; }

extern "C" Pacman *entryPoint() { return instance; }

extern "C" Arcade::ModuleType getType() { return (Arcade::ModuleType::Game); }

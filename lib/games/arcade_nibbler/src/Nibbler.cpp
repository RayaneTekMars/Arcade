/*
** EPITECH PROJECT, 2022
** Nibbler.cpp
** File description:
** Nibbler.cpp
*/

#include "../include/Nibbler.hpp"

Nibbler *instance = nullptr;

Nibbler::Nibbler() : Arcade::AGameModule("Nibbler")
{
    m_subPixel = {
        {'_', {{0, 0, 0, 0}, " ", false}},
        {'X', {{0, 0, 0, 0}, "█", false}},
        {'|', {{0, 0, 0, 0}, "║", false}},
        {'-', {{0, 0, 0, 0}, "═", false}},
        {'J', {{0, 0, 0, 0}, "╝", false}},
        {'L', {{0, 0, 0, 0}, "╚", false}},
        {'/', {{0, 0, 0, 0}, "╔", false}},
        {'\\', {{0, 0, 0, 0}, "╗", false}},
        {'#', {{255, 255, 255, 255}, "⬜️", false}},
        {' ', {{48, 59, 70, 255}, "⬛️", false}},
        {'o', {{0, 0, 0, 0}, "⭕", true}},
        {'t', {{255, 0, 0, 255}, "🐸", false}},
        {'p', {{0, 255, 0, 255}, "🍎", false}}
    };
    loadTitle("./lib/games/arcade_nibbler/assets/title/image.png",
        "./lib/games/arcade_nibbler/assets/title/ascii.txt");
    loadScores("./lib/games/arcade_nibbler/data/scores.txt");
    init();
}

Nibbler::~Nibbler() { saveScores("./lib/games/arcade_nibbler/data/scores.txt"); }

void Nibbler::init()
{
    loadMap("./lib/games/arcade_nibbler/assets/map/map.txt");
    m_lives = 1;
    m_score = 0;
    m_state = Arcade::IGameModule::Playing;
    m_coord.clear();
    m_direction = RIGHT;
    for (int i = 0; i < m_map.size(); i++) {
        if (m_coord.size() == 3)
            break;
        for (int y = 0; y < m_map.at(i).size(); y++) {
            if (m_coord.size() == 3)
                break;
            if (m_map[i][y] == 't') {
                m_coord.push_back(std::make_pair(i, y - 1));
                m_coord.push_back(std::make_pair(i, y - 2));
                m_coord.push_back(std::make_pair(i, y - 3));
                break;
            }
        }
    }
}

void Nibbler::spawnFood()
{
    std::srand(std::time(NULL));
    while (1) {
        int i = std::rand() % m_map.size();
        int j = std::rand() % m_map.at(i).size();
        if (m_map[i][j] == ' ' && !bodyContact(i, j)) {
            m_map[i][j] = 'p';
            return;
        }
    }
}

bool Nibbler::bodyContact(int i, int y)
{
    for (int s = 0; s < m_coord.size(); s++) {
        if (m_coord.at(s).first == i && m_coord.at(s).second == y)
            return true;
    }
    return false;
}

void Nibbler::frame(Arcade::KeyboardInput input)
{
    char character;
    if (input.key == Arcade::KeyboardInput::Key::Z && m_direction != BOTTOM)
        m_direction = TOP;
    else if (input.key == Arcade::KeyboardInput::Key::S && m_direction != TOP)
        m_direction = BOTTOM;
    else if (input.key == Arcade::KeyboardInput::Key::D && m_direction != LEFT)
        m_direction = RIGHT;
    else if (input.key == Arcade::KeyboardInput::Key::Q && m_direction != RIGHT)
        m_direction = LEFT;

    for (int i = 0; i < m_map.size(); i++) {
        for (int y = 0; y < m_map.at(i).size(); y++) {
            if (m_map[i][y] == 't' && m_direction == TOP) {
                character = m_map[i - 1][y];
                if (m_map[i - 1][y] == 'p') {
                    m_coord.insert(m_coord.begin(), std::make_pair(i, y));
                    m_map[i][y] = ' ';
                    m_map[i - 1][y] = 't';
                    spawnFood();
                    m_score += 10;
                } else if (m_map[i - 1][y] != '#' && !bodyContact((i - 1), y)) {
                    m_coord.insert(m_coord.begin(), std::make_pair(i, y));
                    m_coord.pop_back();
                    m_map[i][y] = ' ';
                    m_map[i - 1][y] = 't';
                    m_score += 1;
                } else {
                    m_state = Arcade::IGameModule::Lost;
                }
                return;
            } else if (m_map[i][y] == 't' && m_direction == LEFT) {
                character = m_map[i][y - 1];
                if (m_map[i][y - 1] == 'p') {
                    m_coord.insert(m_coord.begin(), std::make_pair(i, y));
                    m_map[i][y] = ' ';
                    m_map[i][y - 1] = 't';
                    spawnFood();
                    m_score += 10;
                } else if (m_map[i][y - 1] != '#' && !bodyContact(i, (y - 1))) {
                    m_coord.insert(m_coord.begin(), std::make_pair(i, y));
                    m_coord.pop_back();
                    m_map[i][y] = ' ';
                    m_map[i][y - 1] = 't';
                    m_score += 1;
                } else {
                    m_state = Arcade::IGameModule::Lost;
                }
                return;
            } else if (m_map[i][y] == 't' && m_direction == BOTTOM) {
                character = m_map[i + 1][y];
                if (m_map[i + 1][y] == 'p') {
                    m_coord.insert(m_coord.begin(), std::make_pair(i, y));
                    m_map[i][y] = ' ';
                    m_map[i + 1][y] = 't';
                    spawnFood();
                    m_score += 10;
                } else if (m_map[i + 1][y] != '#' && !bodyContact((i + 1), y)) {
                    m_coord.insert(m_coord.begin(), std::make_pair(i, y));
                    m_coord.pop_back();
                    m_map[i][y] = ' ';
                    m_map[i + 1][y] = 't';
                    m_score += 1;
                } else {
                    m_state = Arcade::IGameModule::Lost;
                }
                return;
            } else if (m_map[i][y] == 't' && m_direction == RIGHT) {
                character = m_map[i][y + 1];
                if (m_map[i][y + 1] == 'p') {
                    m_coord.insert(m_coord.begin(), std::make_pair(i, y));
                    m_map[i][y] = ' ';
                    m_map[i][y + 1] = 't';
                    spawnFood();
                    m_score += 10;
                } else if (m_map[i][y + 1] != '#' && !bodyContact(i, (y + 1))) {
                    m_coord.insert(m_coord.begin(), std::make_pair(i, y));
                    m_coord.pop_back();
                    m_map[i][y] = ' ';
                    m_map[i][y + 1] = 't';
                    m_score += 1;
                } else {
                    m_state = Arcade::IGameModule::Lost;
                }
                return;
            }
        }
    }
}

// lorsque le serpent mange la pomme, il faudrait juste eviter de supprimer le maillon de la fin et
// rajouter la précédente coordonnée de t au début

const std::vector<std::string> &Nibbler::getMap()
{
    m_mapTmp.assign(m_map.begin(), m_map.end());

    for (int i = 0; i < m_coord.size(); i++)
        m_mapTmp[m_coord.at(i).first][m_coord.at(i).second] = 'o';
    return (m_mapTmp);
}

void Nibbler::victory()
{
    int count = 0;
    for (int i = 0; i < m_map.size(); i++) {
        for (int y = 0; y < m_map.at(i).size(); y++) {
            if (m_map[i][y] == ' ')
                count++;
            else if (m_map[i][y] == 'p')
                m_state = Arcade::IGameModule::Playing;
        }
    }
    if (count == m_coord.size())
        m_state = Arcade::IGameModule::Won;
    m_state = Arcade::IGameModule::Playing;
}

void loadNibbler() { instance = new Nibbler; }

void unloadNibbler() { delete instance; }

extern "C" Nibbler *entryPoint() { return (instance); }

extern "C" Arcade::ModuleType getType() { return (Arcade::ModuleType::Game); }

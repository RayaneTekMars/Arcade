/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** DisplayNcurse
*/

#include "../include/DisplayNcurse.hpp"

#include <algorithm>
#include <iostream>
#include <locale>

DisplayNcurse *instance = nullptr;

DisplayNcurse::DisplayNcurse() : ADisplayModule("Ncurses"), m_enter(false)
{
    m_arcade = Title("./assets/title/image.png", "./assets/title/ascii.txt");
    m_gameover = Title("./assets/gameover/image.png", "./assets/gameover/ascii.txt");
    m_victory = Title("./assets/victory/image.png", "./assets/victory/ascii.txt");
    m_subPixel = {
        { '_',   {{0, 0, 0, 0}, " ", false}},
        { 'X', {{0, 0, 0, 0}, "█", false}},
        { '|', {{0, 0, 0, 0}, "║", false}},
        { '-', {{0, 0, 0, 0}, "═", false}},
        { 'J', {{0, 0, 0, 0}, "╝", false}},
        { 'L', {{0, 0, 0, 0}, "╚", false}},
        { '/', {{0, 0, 0, 0}, "╔", false}},
        {'\\', {{0, 0, 0, 0}, "╗", false}}
    };
}

DisplayNcurse::~DisplayNcurse() { stop(); }

void DisplayNcurse::init()
{
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, true);
    noecho();
    cbreak();
    nodelay(stdscr, true);
    curs_set(0);
    clear();
}

void DisplayNcurse::initGame(const Title &title, const std::map<char, Arcade::Pixel> &subPixel)
{
    m_title = title;
    m_gamePixel = subPixel;
}

void DisplayNcurse::stop() { endwin(); }

bool DisplayNcurse::displayMainMenu(const Arcade::KeyboardInput &key,
    const std::vector<Arcade::IDisplayModule *> &libs,
    const std::vector<Arcade::IGameModule *> &games, std::string &username, int &choice)
{
    int x = 0, y = 0;

    clear();
    getmaxyx(stdscr, y, x);
    for (int i = 0; i < m_arcade.ascii.size(); i++) {
        for (int j = 0; j < m_arcade.ascii[i].size(); j++) {
            if (m_subPixel.contains(m_arcade.ascii[i][j])) {
                mvaddstr(i + ((y / 2) - (m_arcade.ascii.size() / 2)),
                    j + ((x / 2) - (m_arcade.ascii[i].size() / 2)),
                    m_subPixel.at(m_arcade.ascii[i][j]).s.c_str());
            } else {
                mvaddch(i + ((y / 2) - (m_arcade.ascii.size() / 2)),
                    j + ((x / 2) - (m_arcade.ascii[i].size() / 2)), m_arcade.ascii[i][j]);
            }
        }
    }
    if (!m_enter) {
        if (key.key == Arcade::KeyboardInput::Key::UP)
            choice = ((choice == 0) ? (static_cast<int>(games.size()) - 1) : (choice - 1));
        else if (key.key == Arcade::KeyboardInput::Key::DOWN)
            choice = ((choice == (static_cast<int>(games.size()) - 1)) ? 0 : (choice + 1));
        else if (key.key == Arcade::KeyboardInput::Key::ENTER)
            m_enter = true;

        mvaddstr(((y / 2) + (m_arcade.ascii.size() / 2)) + 2, ((x / 2) - 21),
            "Press ↑↓ to select a game and ENTER to continue");

        for (int i = 0; i < games.size(); i++) {
            if (i == choice)
                attron(A_STANDOUT);
            mvaddstr(((y / 2) + (m_arcade.ascii.size() / 2)) + 4 + (i * 2),
                ((x / 2) - (games[i]->getName().size() / 2)), games[i]->getName().c_str());
            attroff(A_STANDOUT);
        }
    } else {
        mvaddstr(((y / 2) + (m_arcade.ascii.size() / 2)) + 2, ((x / 2) - 22),
            "Enter your USERNAME and press ENTER to play");

        if (key.key == Arcade::KeyboardInput::Key::ENTER && !username.empty()) {
            m_enter = false;
            return (true);
        }
        if ((key.code >= 0 && key.code <= 127) &&std::isprint(key.code))
            username += static_cast<char>(key.code);
        else if (key.code == KEY_BACKSPACE && !username.empty())
            username.pop_back();
        mvprintw(((y / 2) + (m_arcade.ascii.size() / 2)) + 4,
            ((x / 2) - ((10 + username.size()) / 2)), "Username: %s", username.c_str());
    }
    refresh();
    return (false);
}

void DisplayNcurse::displayGame(const std::vector<std::string> &map,
    const std::map<std::string, std::size_t> &scores, std::size_t score, std::size_t lives)
{
    int x = 0, y = 0, y_offset = 0;

    clear();
    getmaxyx(stdscr, y, x);
    y_offset = ((y / 2) - ((m_title.ascii.size() + map.size() + 8) / 2)) + 2;
    for (int i = 0; i < m_title.ascii.size(); i++) {
        for (int j = 0; j < m_title.ascii[i].size(); j++) {
            if (m_gamePixel.contains(m_title.ascii[i][j])) {
                mvaddstr(y_offset + i, j + ((x / 2) - (m_title.ascii[i].size() / 2)),
                    m_gamePixel.at(m_title.ascii[i][j]).s.c_str());
            } else {
                mvaddch(y_offset + i, j + ((x / 2) - (m_title.ascii[i].size() / 2)),
                    m_title.ascii[i][j]);
            }
        }
    }
    y_offset += (m_title.ascii.size() + 2);
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (m_gamePixel.contains(map[i][j])) {
                mvaddstr(y_offset + i, j + ((x / 2) - map[i].size()),
                    m_gamePixel.at(map[i][j]).s.c_str());
            } else {
                mvaddch(y_offset + i, j + ((x / 2) - map[i].size()), map[i][j]);
            }
        }
    }
    y_offset += map.size();
    mvaddstr(y_offset + 1, (x / 2) - map[0].size(), "Best Score :");
    auto best = std::max_element(
        scores.begin(), scores.end(), [](auto &a, auto &b) { return (a.second < b.second); });
    if (best != scores.end())
        mvprintw(y_offset + 3, (x / 2) - map[0].size(), "%s : %010zu", best->first.c_str(),
            best->second);
    mvprintw(y_offset + 1, (x / 2) - 4, "Lives : %zu", lives);
    mvaddstr(y_offset + 1, (x / 2) + map[0].size() - 7, "Score :");
    mvprintw(y_offset + 3, (x / 2) + map[0].size() - 10, "%010zu", score);
    refresh();
}

void DisplayNcurse::displayVictory(const std::string username, std::size_t scores)
{
    int x, y;

    clear();
    getmaxyx(stdscr, y, x);
    for (int i = 0; i < m_victory.ascii.size(); i++) {
        for (int j = 0; j < m_victory.ascii[i].size(); j++) {
            if (m_subPixel.contains(m_victory.ascii[i][j])) {
                mvaddstr(i + ((y / 2) - (m_victory.ascii.size() / 2)),
                    j + ((x / 2) - (m_victory.ascii[i].size() / 2)),
                    m_subPixel.at(m_victory.ascii[i][j]).s.c_str());
            } else {
                mvaddch(i + ((y / 2) - (m_victory.ascii.size() / 2)),
                    j + ((x / 2) - (m_victory.ascii[i].size() / 2)), m_victory.ascii[i][j]);
            }
        }
    }
    mvprintw(m_victory.ascii.size() + ((y / 2) - (m_victory.ascii.size() / 2) + 2),
        (x / 2) - ((9 + username.size()) / 2), "Player : %s", username.c_str());
    mvprintw(m_victory.ascii.size() + ((y / 2) - (m_victory.ascii.size() / 2) + 3), (x / 2) - 9,
        "Score : %010zu", scores);
    mvprintw(m_victory.ascii.size() + ((y / 2) - (m_victory.ascii.size() / 2) + 5), (x / 2) - 18,
        "Press ESC to quit or ENTER to restart");
    refresh();
}

void DisplayNcurse::displayGameover(const std::string username, std::size_t scores)
{
    int x, y;

    clear();
    getmaxyx(stdscr, y, x);
    for (int i = 0; i < m_gameover.ascii.size(); i++) {
        for (int j = 0; j < m_gameover.ascii[i].size(); j++) {
            if (m_subPixel.contains(m_gameover.ascii[i][j])) {
                mvaddstr(i + ((y / 2) - (m_gameover.ascii.size() / 2)),
                    j + ((x / 2) - (m_gameover.ascii[i].size() / 2)),
                    m_subPixel.at(m_gameover.ascii[i][j]).s.c_str());
            } else {
                mvaddch(i + ((y / 2) - (m_gameover.ascii.size() / 2)),
                    j + ((x / 2) - (m_gameover.ascii[i].size() / 2)), m_gameover.ascii[i][j]);
            }
        }
    }
    mvprintw(m_gameover.ascii.size() + ((y / 2) - (m_gameover.ascii.size() / 2) + 2),
        (x / 2) - ((9 + username.size()) / 2), "Player : %s", username.c_str());
    mvprintw(m_gameover.ascii.size() + ((y / 2) - (m_gameover.ascii.size() / 2) + 3), (x / 2) - 9,
        "Score : %010zu", scores);
    mvprintw(m_gameover.ascii.size() + ((y / 2) - (m_gameover.ascii.size() / 2) + 5), (x / 2) - 18,
        "Press ESC to quit or ENTER to restart");
    refresh();
}

Arcade::KeyboardInput DisplayNcurse::getInput()
{
    using Key = Arcade::KeyboardInput::Key;
    int key = getch();

    switch (key) {
        case 10:
            return (Arcade::KeyboardInput(Key::ENTER, key));
        case 'e':
            return (Arcade::KeyboardInput(Key::E, key));
        case 'z':
            return (Arcade::KeyboardInput(Key::Z, key));
        case 'q':
            return (Arcade::KeyboardInput(Key::Q, key));
        case 's':
            return (Arcade::KeyboardInput(Key::S, key));
        case 'd':
            return (Arcade::KeyboardInput(Key::D, key));
        case 'p':
            return (Arcade::KeyboardInput(Key::P, key));
        case 'r':
            return (Arcade::KeyboardInput(Key::R, key));
        case KEY_UP:
            return (Arcade::KeyboardInput(Key::UP, key));
        case KEY_DOWN:
            return (Arcade::KeyboardInput(Key::DOWN, key));
        case KEY_LEFT:
            return (Arcade::KeyboardInput(Key::LEFT, key));
        case KEY_RIGHT:
            return (Arcade::KeyboardInput(Key::RIGHT, key));
        case ' ':
            return (Arcade::KeyboardInput(Key::SPACE, key));
        case 27:
            return (Arcade::KeyboardInput(Key::ESCAPE, key));
        default:
            break;
    }
    return (Arcade::KeyboardInput(Key::NN, key));
}

void loadDisplayNcurse() { instance = new DisplayNcurse; }

void unloadDisplayNcurse() { delete instance; }

extern "C" DisplayNcurse *entryPoint() { return (instance); }

extern "C" Arcade::ModuleType getType() { return (Arcade::ModuleType::Display); }
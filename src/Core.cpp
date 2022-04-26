/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Core
*/

#include "Core.hpp"

namespace Arcade
{
    const std::string Core::m_usage =
        "USAGE:\n"
        "  ./arcade path_to_graphical_lib\n"
        "\n"
        "DESCRIPTION:\n"
        "  lib          path to the initial graphical library to load (./lib/arcade_lib_name.so)\n"
        "\n"
        "COMMANDS:\n"
        "  RIGHT ARROW  next graphic lib\n"
        "  LEFT ARROW   previous graphic lib\n"
        "  UP ARROW     next game lib\n"
        "  DOWN ARROW   previous game lib\n"
        "\n"
        "  ENTER        restart the game (only available when game finish)\n"
        "  ESC          quit arcade or return to menu\n"
        "\n"
        "  D            move right\n"
        "  Q            move left\n"
        "  Z            move up\n"
        "  S            move down";

    Core::Exception::Exception(const std::string &message) : m_message(message) {}

    Core::Exception::~Exception() {}

    const char *Core::Exception::what() const noexcept { return m_message.c_str(); }

    Core::UsageException::UsageException() : Core::Exception(m_usage) {}

    Core::UsageException::~UsageException() {}

    Core::Core() : m_username(""), m_menu(true), m_open(true), m_gameChoice(0), m_libChoice(0) {}

    Core::~Core() {}

    void Core::init(int ac, char **av)
    {
        auto lib = std::make_unique<Arcade::DLLoader>();

        if (ac != 2)
            throw UsageException();
        m_libinit.assign(av[1]);
        if (!fs::exists(m_libinit) || !fs::is_regular_file(m_libinit))
            throw Exception("Core: library path does not exist");

        try {
            lib->load(m_libinit);
            if (lib->getType() == Arcade::Display) {
                m_dispMod.push_back(lib->getInstance<Arcade::IDisplayModule>());
            } else {
                throw Exception("Core: unknown type");
            }
            m_dll.push_back(std::move(lib));
        } catch (Arcade::DLLoader::Exception &e) {
            throw Exception(std::string("Core: ") + e.what());
        }
        loadLibs();
    }

    void Core::loop()
    {
        std::chrono::time_point<std::chrono::steady_clock> fpsTimer(
            std::chrono::steady_clock::now());
        std::chrono::duration<int32_t, std::ratio<1, 15>> FPS{};

        m_dispMod[m_libChoice]->init();
        while (m_open) {
            FPS = std::chrono::duration_cast<std::chrono::duration<int32_t, std::ratio<1, 15>>>(
                std::chrono::steady_clock::now() - fpsTimer);
            if (FPS.count() >= 1) {
                m_key = m_dispMod[m_libChoice]->getInput();
                fpsTimer = std::chrono::steady_clock::now();
                swapDisplays();
                if (m_menu) {
                    loopMenu();
                } else {
                    swapGames();
                    loopGame();
                }
            }
            // usleep(100000);
        }
        m_dispMod[m_libChoice]->stop();
    }

    void Core::loadLibs()
    {
        std::regex lib("^arcade_\\w+\\.so$");

        for (const auto &entry : fs::directory_iterator("./lib")) {
            if (entry.status().type() == fs::file_type::regular
                && std::regex_match(entry.path().filename().c_str(), lib)
                && m_libinit.filename() != entry.path().filename()) {
                auto lib = std::make_unique<Arcade::DLLoader>();
                try {
                    lib->load(entry.path());
                    switch (lib->getType()) {
                        case Arcade::Game:
                            m_gameMod.push_back(lib->getInstance<Arcade::IGameModule>());
                            break;
                        case Arcade::Display:
                            m_dispMod.push_back(lib->getInstance<Arcade::IDisplayModule>());
                            break;
                        default:
                            throw Exception("Core: unknown type");
                    }
                    m_dll.push_back(std::move(lib));
                } catch (Arcade::DLLoader::Exception &e) {
                    throw Exception(std::string("Core: ") + e.what());
                }
            }
        }

        if (m_dispMod.empty())
            throw Exception("Core: no display module found");
        else if (m_gameMod.empty())
            throw Exception("Core: no game module found");
    }

    void Core::swapDisplays()
    {
        if (m_key.key == Arcade::KeyboardInput::Key::RIGHT) {
            m_dispMod[m_libChoice]->stop();
            m_libChoice =
                ((m_libChoice == (static_cast<int>(m_dispMod.size()) - 1)) ? 0 : (m_libChoice + 1));
            m_dispMod[m_libChoice]->init();
            m_dispMod[m_libChoice]->initGame(
                m_gameMod[m_gameChoice]->getTitle(), m_gameMod[m_gameChoice]->getSubPixel());
        } else if (m_key.key == Arcade::KeyboardInput::Key::LEFT) {
            m_dispMod[m_libChoice]->stop();
            m_libChoice =
                ((m_libChoice == 0) ? (static_cast<int>(m_dispMod.size()) - 1) : (m_libChoice - 1));
            m_dispMod[m_libChoice]->init();
            m_dispMod[m_libChoice]->initGame(
                m_gameMod[m_gameChoice]->getTitle(), m_gameMod[m_gameChoice]->getSubPixel());
        }
    }

    void Core::swapGames()
    {
        if (m_key.key == Arcade::KeyboardInput::Key::UP) {
            m_gameChoice =
                ((m_gameChoice == (static_cast<int>(m_gameMod.size()) - 1)) ? 0
                                                                            : (m_gameChoice + 1));
            m_dispMod[m_libChoice]->initGame(
                m_gameMod[m_gameChoice]->getTitle(), m_gameMod[m_gameChoice]->getSubPixel());
        } else if (m_key.key == Arcade::KeyboardInput::Key::DOWN) {
            m_gameChoice = ((m_gameChoice == 0) ? (static_cast<int>(m_gameMod.size()) - 1)
                                                : (m_gameChoice - 1));
            m_dispMod[m_libChoice]->initGame(
                m_gameMod[m_gameChoice]->getTitle(), m_gameMod[m_gameChoice]->getSubPixel());
        }
    }

    void Core::loopGame()
    {
        if (m_key.key == Arcade::KeyboardInput::Key::ESCAPE) {
            m_gameMod[m_gameChoice]->init();
            m_menu = true;
        } else if (m_gameMod[m_gameChoice]->getState() == Arcade::IGameModule::Lost) {
            m_gameMod[m_gameChoice]->setScores(m_username, m_gameMod[m_gameChoice]->getScore());
            m_dispMod[m_libChoice]->displayGameover(
                m_username, m_gameMod[m_gameChoice]->getScore());
            if (m_key.key == Arcade::KeyboardInput::Key::ENTER) {
                m_gameMod[m_gameChoice]->init();
                return;
            }
        } else if (m_gameMod[m_gameChoice]->getState() == Arcade::IGameModule::Won) {
            m_gameMod[m_gameChoice]->setScores(m_username, m_gameMod[m_gameChoice]->getScore());
            m_dispMod[m_libChoice]->displayVictory(m_username, m_gameMod[m_gameChoice]->getScore());
            if (m_key.key == Arcade::KeyboardInput::Key::ENTER) {
                m_gameMod[m_gameChoice]->init();
                return;
            } else if (m_key.key == Arcade::KeyboardInput::Key::ESCAPE) {
                m_gameMod[m_gameChoice]->init();
                m_menu = true;
            }
        } else {
            m_gameMod[m_gameChoice]->frame(m_key);
            m_dispMod[m_libChoice]->displayGame(m_gameMod[m_gameChoice]->getMap(),
                m_gameMod[m_gameChoice]->getScores(), m_gameMod[m_gameChoice]->getScore(),
                m_gameMod[m_gameChoice]->getLives());
        }
    }

    void Core::loopMenu()
    {
        if (m_key.key == Arcade::KeyboardInput::Key::ESCAPE)
            m_open = false;
        else if (m_dispMod[m_libChoice]->displayMainMenu(
                     m_key, m_dispMod, m_gameMod, m_username, m_gameChoice)) {
            m_dispMod[m_libChoice]->initGame(
                m_gameMod[m_gameChoice]->getTitle(), m_gameMod[m_gameChoice]->getSubPixel());
            m_menu = false;
        }
    }

} // namespace Arcade
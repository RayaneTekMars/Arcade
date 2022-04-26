/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** ADisplayModule
*/

#include "../../include/ADisplayModule.hpp"

namespace Arcade
{
    ADisplayModule::ADisplayModule(const std::string &name) : m_name(name) {}

    ADisplayModule::~ADisplayModule() {}

    void ADisplayModule::init() {}

    void ADisplayModule::initGame(const Title &title, const std::map<char, Pixel> &subPixel) {}

    void ADisplayModule::stop() {}

    bool ADisplayModule::displayMainMenu(const Arcade::KeyboardInput &key,
        const std::vector<Arcade::IDisplayModule *> &libs,
        const std::vector<Arcade::IGameModule *> &games, std::string &username, int &choice)
    {
        return (false);
    }

    void ADisplayModule::displayGame(const std::vector<std::string> &map,
        const std::map<std::string, std::size_t> &scores, std::size_t score, std::size_t lifes)
    {}

    void ADisplayModule::displayVictory(const std::string username, std::size_t scores) {}

    void ADisplayModule::displayGameover(const std::string username, std::size_t scores) {}

    const std::string &ADisplayModule::getName() { return (m_name); }

    KeyboardInput ADisplayModule::getInput() { return (KeyboardInput()); }

} // namespace Arcade
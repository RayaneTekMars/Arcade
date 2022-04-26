/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** AGameModule
*/

#include "AGameModule.hpp"

namespace Arcade
{
    AGameModule::AGameModule(const std::string &name) : m_state(Playing), m_name(name), m_score(0UL)
    {}

    AGameModule::~AGameModule() {}

    void AGameModule::init() {}

    void AGameModule::frame(KeyboardInput input) {}

    void AGameModule::setScores(const std::string &username, size_t score)
    {
        if (!m_leaderBoard.contains(username) || m_leaderBoard[username] < score)
            m_leaderBoard[username] = score;
    }

    AGameModule::GameState AGameModule::getState() { return (m_state); }

    std::size_t AGameModule::getLives() { return (m_lives); }

    std::size_t AGameModule::getScore() { return (m_score); }

    const Title &AGameModule::getTitle() { return (m_title); }

    const std::string &AGameModule::getName() { return (m_name); }

    const std::vector<std::string> &AGameModule::getMap() { return (m_map); }

    const std::map<char, Pixel> &AGameModule::getSubPixel() { return (m_subPixel); }

    const std::map<std::string, std::size_t> &AGameModule::getScores() { return (m_leaderBoard); }

    void AGameModule::loadMap(const std::string &filename)
    {
        std::ifstream file(filename);
        std::string buffer;

        m_map.clear();
        if (file.is_open())
            while (std::getline(file, buffer, '\n')) m_map.push_back(std::move(buffer));
        else
            throw;
    }

    void AGameModule::loadTitle(const std::string &image, const std::string &ascii)
    {
        std::ifstream file(ascii);
        std::string buffer;

        m_title.image = image;
        if (file.is_open()) {
            m_title.image = image;
            while (std::getline(file, buffer, '\n')) m_title.ascii.push_back(std::move(buffer));
        } else
            throw;
    }

    void AGameModule::loadScores(const std::string &filename)
    {
        std::ifstream file(filename);
        std::string buffer;

        std::regex score("\\s*(\\w+)\\s+(\\d+)");

        m_leaderBoard.clear();
        if (file.is_open()) {
            std::getline(file, buffer, '\0');
            buffer.assign(std::regex_replace(buffer, std::regex("\\s*#.*"), ""));

            auto begin = std::sregex_iterator(buffer.begin(), buffer.end(), score);
            auto end = std::sregex_iterator();

            for (auto i = begin; i != end; ++i) setScores(i->str(1), std::stoul(i->str(2)));
        } else {
            throw;
        }
    }

    void AGameModule::saveScores(const std::string &filename)
    {
        std::ofstream file(filename, std::ios::trunc);

        if (file.is_open()) {
            file << "#\tUSERNAME\t#\tSCORE\t#" << std::endl;
            for (auto a : m_leaderBoard)
                file << "\t" << a.first << "\t\t" << a.second << std::endl;
        } else {
            throw;
        }
    }
} // namespace Arcade
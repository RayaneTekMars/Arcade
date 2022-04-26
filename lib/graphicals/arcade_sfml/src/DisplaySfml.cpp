/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Espace de travail)
** File description:
** DisplaySfml
*/

#include "../include/DisplaySfml.hpp"

#include <iostream>

DisplaySfml *instance = nullptr;

sf::Font DisplaySfml::m_font;
sf::Text DisplaySfml::m_text;
sf::Sprite DisplaySfml::m_sprite;
sf::Texture DisplaySfml::m_texture;

DisplaySfml::DisplaySfml() : ADisplayModule("SFML"), m_enter(false), m_window(nullptr)
{
    m_arcade = Title("./assets/title/image.png", "./assets/title/ascii.txt");
    m_gameover = Title("./assets/gameover/image.png", "./assets/gameover/ascii.txt");
    m_victory = Title("./assets/victory/image.png", "./assets/victory/ascii.txt");
}

DisplaySfml::~DisplaySfml() { stop(); }

void DisplaySfml::init()
{
    m_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade", sf::Style::Fullscreen);
    m_window->setFramerateLimit(60);
    m_font.loadFromFile("./assets/font/pixel.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(30);
    m_text.setFillColor(sf::Color::White);
    m_rectangle.setSize(sf::Vector2f(20, 20));
    m_circle.setRadius(5);
}

void DisplaySfml::initGame(const Title &title, const std::map<char, Arcade::Pixel> &subPixel)
{
    m_title = title;
    m_gamePixel = subPixel;
}

void DisplaySfml::stop()
{
    if (m_window) {
        m_window->close();
        m_window = nullptr;
    }
}

bool DisplaySfml::displayMainMenu(const Arcade::KeyboardInput &key,
    const std::vector<Arcade::IDisplayModule *> &libs,
    const std::vector<Arcade::IGameModule *> &games, std::string &username, int &choice)
{
    int y_offset = 0;

    m_window->clear(sf::Color::Black);

    m_texture.loadFromFile(m_arcade.image);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(0, 0);
    m_window->draw(m_sprite);

    if (!m_enter) {
        if (key.key == Arcade::KeyboardInput::Key::UP)
            choice = ((choice == 0) ? (static_cast<int>(games.size()) - 1) : (choice - 1));
        else if (key.key == Arcade::KeyboardInput::Key::DOWN)
            choice = ((choice == (static_cast<int>(games.size()) - 1)) ? 0 : (choice + 1));
        else if (key.key == Arcade::KeyboardInput::Key::ENTER)
            m_enter = true;
        // Press UP / DOWN to select a game and ENTER to continue
        m_text.setString("Press UP / DOWN to select a game and ENTER to continue");
        m_text.setPosition(
            sf::Vector2f(m_window->getSize().x / 2 - m_text.getGlobalBounds().width / 2,
                m_window->getSize().y / 2 - m_text.getGlobalBounds().height / 2));
        y_offset = m_text.getPosition().y + m_text.getGlobalBounds().height;
        m_window->draw(m_text);
        // game choice
        for (int i = 0; i < games.size(); i++) {
            if (i == choice)
                m_text.setFillColor(sf::Color::Red);
            m_text.setString(games[i]->getName());
            m_text.setPosition(
                sf::Vector2f(m_window->getSize().x / 2 - m_text.getGlobalBounds().width / 2,
                    y_offset + 50 + (i * (m_text.getGlobalBounds().height * 2))));
            m_window->draw(m_text);
            m_text.setFillColor(sf::Color::White);
        }
    } else {
        // choice your name
        m_text.setString("Enter your USERNAME and press ENTER to play");
        m_text.setPosition(
            sf::Vector2f(m_window->getSize().x / 2 - m_text.getGlobalBounds().width / 2,
                m_window->getSize().y / 2 - m_text.getGlobalBounds().height / 2));
        y_offset = m_text.getPosition().y + m_text.getGlobalBounds().height;
        m_window->draw(m_text);

        if (key.code == 13 && !username.empty()) {
            m_enter = false;
            return (true);
        }
        if (std::isprint(key.code))
            username += static_cast<char>(key.code);
        else if (key.code == 8 && !username.empty())
            username.pop_back();
        m_text.setString("Username: " + username);
        m_text.setPosition(
            sf::Vector2f(m_window->getSize().x / 2 - m_text.getGlobalBounds().width / 2,
                y_offset + m_text.getGlobalBounds().height + 50));
        m_window->draw(m_text);
    }
    m_window->display();
    return (false);
}

void DisplaySfml::displayGame(const std::vector<std::string> &map,
    const std::map<std::string, std::size_t> &scores, std::size_t score, std::size_t lives)
{
    Arcade::Color color;
    int y_offset = 0;

    m_window->clear(sf::Color::Black);

    m_texture.loadFromFile(m_title.image);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(0, 0);
    m_window->draw(m_sprite);

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            m_circle.setPosition((1920 / 2) - ((map[i].size() * 20) / 2) + (j * 20) + 5,
                (1080 / 2) - ((map.size() * 20) / 2) + (i * 20) + 5);
            m_rectangle.setPosition((1920 / 2) - ((map[i].size() * 20) / 2) + (j * 20),
                (1080 / 2) - ((map.size() * 20) / 2) + (i * 20));
            if (m_gamePixel.contains(map[i][j])) {
                if (map[i][j] == 'x') {
                    color = m_gamePixel[' '].c;
                    m_rectangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
                    m_window->draw(m_rectangle);
                    m_circle.setFillColor(sf::Color::Yellow);
                    m_window->draw(m_circle);
                } else {
                    color = m_gamePixel[map[i][j]].c;
                    m_rectangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
                    m_window->draw(m_rectangle);
                }
            }
        }
    }

    m_text.setString("Best Score: ");
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - ((static_cast<int>(map[0].size()) * 20) / 2),
            (m_window->getSize().y / 2) + (static_cast<int>(map.size() / 2) * 20)
                + m_text.getGlobalBounds().height));
    y_offset = m_text.getPosition().y + m_text.getGlobalBounds().height;
    m_window->draw(m_text);

    auto best = std::max_element(
        scores.begin(), scores.end(), [](auto &a, auto &b) { return (a.second < b.second); });

    m_text.setString(best->first + " " + std::to_string(best->second));
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - ((static_cast<int>(map[0].size()) * 20) / 2),
            y_offset + m_text.getGlobalBounds().height));
    m_window->draw(m_text);

    m_text.setString("Lives: " + std::to_string(lives));
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - (m_text.getGlobalBounds().width / 2),
            (m_window->getSize().y / 2) + (static_cast<int>(map.size() / 2) * 20)
                + m_text.getGlobalBounds().height));
    m_window->draw(m_text);

    m_text.setString("Score: ");
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) + ((static_cast<int>(map[0].size()) * 20) / 2)
                         - m_text.getGlobalBounds().width,
            (m_window->getSize().y / 2) + (static_cast<int>(map.size() / 2) * 20)
                + m_text.getGlobalBounds().height));
    y_offset = m_text.getPosition().y + m_text.getGlobalBounds().height;
    m_window->draw(m_text);

    m_text.setString(std::to_string(score));
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) + ((static_cast<int>(map[0].size()) * 20) / 2)
                         - m_text.getGlobalBounds().width,
            y_offset + m_text.getGlobalBounds().height));
    m_window->draw(m_text);

    m_window->display();
}

void DisplaySfml::displayVictory(const std::string username, std::size_t scores)
{
    int y_offset = 0;

    m_window->clear(sf::Color::Black);

    // display victory title
    m_text.setString("VICTORY");
    m_text.setCharacterSize(300);
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - (m_text.getGlobalBounds().width / 2),
            ((m_window->getSize().y / 2) - (m_text.getGlobalBounds().height / 2) - 250)));
    y_offset = m_text.getPosition().y + m_text.getGlobalBounds().height + 175;
    m_window->draw(m_text);
    m_text.setCharacterSize(30);
    // display Player name
    m_text.setString("Player : " + username);
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - (m_text.getGlobalBounds().width / 2),
            y_offset + m_text.getGlobalBounds().height));
    y_offset = m_text.getPosition().y + m_text.getGlobalBounds().height;
    m_window->draw(m_text);
    // display Player score
    m_text.setString("Score : " + std::to_string(scores));
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - (m_text.getGlobalBounds().width / 2),
            y_offset + m_text.getGlobalBounds().height));
    y_offset = m_text.getPosition().y + m_text.getGlobalBounds().height + 50;
    m_window->draw(m_text);
    // display "Press ESC to quit or ENTER to restart"
    m_text.setString("Press ESC to quit or ENTER to restart");
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - (m_text.getGlobalBounds().width / 2),
            y_offset + m_text.getGlobalBounds().height));
    m_window->draw(m_text);

    m_window->display();
}

void DisplaySfml::displayGameover(const std::string username, std::size_t scores)
{
    int y_offset = 0;

    m_window->clear(sf::Color::Black);

    // display gameover title
    m_text.setString("GAME OVER");
    m_text.setCharacterSize(300);
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - (m_text.getGlobalBounds().width / 2),
            ((m_window->getSize().y / 2) - (m_text.getGlobalBounds().height / 2) - 250)));
    y_offset = m_text.getPosition().y + m_text.getGlobalBounds().height + 175;
    m_window->draw(m_text);
    m_text.setCharacterSize(30);
    // display Player name
    m_text.setString("Player : " + username);
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - (m_text.getGlobalBounds().width / 2),
            y_offset + m_text.getGlobalBounds().height));
    y_offset = m_text.getPosition().y + m_text.getGlobalBounds().height;
    m_window->draw(m_text);
    // display Player score
    m_text.setString("Score : " + std::to_string(scores));
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - (m_text.getGlobalBounds().width / 2),
            y_offset + m_text.getGlobalBounds().height));
    y_offset = m_text.getPosition().y + m_text.getGlobalBounds().height + 50;
    m_window->draw(m_text);
    // display "Press ESC to quit or ENTER to restart"
    m_text.setString("Press ESC to quit or ENTER to restart");
    m_text.setPosition(
        sf::Vector2f((m_window->getSize().x / 2) - (m_text.getGlobalBounds().width / 2),
            y_offset + m_text.getGlobalBounds().height));
    m_window->draw(m_text);

    m_window->display();
}

Arcade::KeyboardInput DisplaySfml::getInput()
{
    sf::Event event;
    using Key = Arcade::KeyboardInput::Key;

    while (m_window->pollEvent(event)) {
        if (m_enter && event.type == sf::Event::TextEntered) {
            return (Arcade::KeyboardInput(Key::NN, event.text.unicode));
        } else if (!m_enter && event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Return:
                    return (Arcade::KeyboardInput(Key::ENTER, event.key.code));
                case sf::Keyboard::E:
                    return (Arcade::KeyboardInput(Key::E, event.key.code));
                case sf::Keyboard::Z:
                    return (Arcade::KeyboardInput(Key::Z, event.key.code));
                case sf::Keyboard::Q:
                    return (Arcade::KeyboardInput(Key::Q, event.key.code));
                case sf::Keyboard::S:
                    return (Arcade::KeyboardInput(Key::S, event.key.code));
                case sf::Keyboard::D:
                    return (Arcade::KeyboardInput(Key::D, event.key.code));
                case sf::Keyboard::P:
                    return (Arcade::KeyboardInput(Key::P, event.key.code));
                case sf::Keyboard::Up:
                    return (Arcade::KeyboardInput(Key::UP, event.key.code));
                case sf::Keyboard::Down:
                    return (Arcade::KeyboardInput(Key::DOWN, event.key.code));
                case sf::Keyboard::Left:
                    return (Arcade::KeyboardInput(Key::LEFT, event.key.code));
                case sf::Keyboard::Right:
                    return (Arcade::KeyboardInput(Key::RIGHT, event.key.code));
                case sf::Keyboard::Space:
                    return (Arcade::KeyboardInput(Key::SPACE, event.key.code));
                case sf::Keyboard::Escape:
                    return (Arcade::KeyboardInput(Key::ESCAPE, event.key.code));
                default:
                    return (Arcade::KeyboardInput(Key::NN, event.key.code));
            }
        }
    }
    return (Arcade::KeyboardInput(Key::NN, -1));
}

void loadDisplaySfml() { instance = new DisplaySfml; }

void unloadDisplaySfml() { delete instance; }

extern "C" DisplaySfml *entryPoint() { return (instance); }

extern "C" Arcade::ModuleType getType() { return (Arcade::ModuleType::Display); }
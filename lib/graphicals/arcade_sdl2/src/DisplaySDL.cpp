/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** DisplaySDL
*/

#include "../include/DisplaySDL.hpp"

#include <algorithm>
#include <iostream>
#include <locale>

DisplaySDL *instance = nullptr;

DisplaySDL::DisplaySDL() : ADisplayModule("SDL2"), m_enter(false), m_window(nullptr), m_renderer(nullptr), m_font(nullptr), m_surface(nullptr), m_texture(nullptr), m_textureRect({0, 0, 0, 0})
{
    m_arcade = Title("./assets/title/image.png", "./assets/title/ascii.txt");
    m_gameover = Title("./assets/gameover/image.png", "./assets/gameover/ascii.txt");
    m_victory = Title("./assets/victory/image.png", "./assets/victory/ascii.txt");
}

DisplaySDL::~DisplaySDL() { stop(); }

void DisplaySDL::init()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_FULLSCREEN, &m_window, &m_renderer);
    m_rect = {100, 50, 20, 20};
    m_font = TTF_OpenFont("./assets/font/pixel.ttf", 24);
}

void DisplaySDL::initGame(const Title &title, const std::map<char, Arcade::Pixel> &subPixel)
{
    m_title = title;
    m_gamePixel = subPixel;
}

void DisplaySDL::stop()
{
    if (m_font) {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool DisplaySDL::displayMainMenu(const Arcade::KeyboardInput &key,
    const std::vector<Arcade::IDisplayModule *> &libs,
    const std::vector<Arcade::IGameModule *> &games, std::string &username, int &choice)
{
    int y_offset = 0;

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    m_surface = IMG_Load(m_arcade.image.c_str());
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    if (!m_enter) {
        if (key.key == Arcade::KeyboardInput::Key::UP)
            choice = ((choice == 0) ? (static_cast<int>(games.size()) - 1) : (choice - 1));
        else if (key.key == Arcade::KeyboardInput::Key::DOWN)
            choice = ((choice == (static_cast<int>(games.size()) - 1)) ? 0 : (choice + 1));
        else if (key.key == Arcade::KeyboardInput::Key::ENTER)
            m_enter = true;

        m_surface = TTF_RenderText_Solid(
            m_font, "Press UP / DOWN to select a game and ENTER to continue", {255, 255, 255});
        m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
        m_textureRect = {(1920 / 2) - (m_surface->w / 2), (1080 / 2) - (m_surface->h / 2),
            m_surface->w, m_surface->h};
        y_offset = (1080 / 2) - (m_surface->h / 2);
        SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
        SDL_FreeSurface(m_surface);
        SDL_DestroyTexture(m_texture);
        for (int i = 0; i < games.size(); i++) {
            if (i == choice)
                m_surface = TTF_RenderText_Solid(m_font, games[i]->getName().c_str(), {255, 0, 0});
            else
                m_surface =
                    TTF_RenderText_Solid(m_font, games[i]->getName().c_str(), {255, 255, 255});
            m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
            m_textureRect = {(1920 / 2) - (m_surface->w / 2),
                y_offset + ((m_surface->h + 25) * (i + 1)) + 50, m_surface->w, m_surface->h};
            SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
            SDL_FreeSurface(m_surface);
            SDL_DestroyTexture(m_texture);
        }
    } else {
        m_surface = TTF_RenderText_Solid(
            m_font, "Enter your USERNAME and press ENTER to play", {255, 255, 255});
        m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
        m_textureRect = {(1920 / 2) - (m_surface->w / 2), (1080 / 2) - (m_surface->h / 2),
            m_surface->w, m_surface->h};
        y_offset = (1080 / 2) - (m_surface->h / 2);
        SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
        SDL_FreeSurface(m_surface);
        SDL_DestroyTexture(m_texture);

        if (key.key == Arcade::KeyboardInput::Key::ENTER && !username.empty()) {
            m_enter = false;
            return (true);
        }

        if ((key.code >= 0 && key.code <= 127) && std::isprint(key.code))
            username += static_cast<char>(key.code);
        else if (key.code == SDLK_BACKSPACE && !username.empty())
            username.pop_back();
        m_surface =
            TTF_RenderText_Solid(m_font, ("Username: " + username).c_str(), {255, 255, 255});
        m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
        m_textureRect = {(1920 / 2) - (m_surface->w / 2), y_offset + m_surface->h + 75,
            m_surface->w, m_surface->h};
        SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
        SDL_FreeSurface(m_surface);
        SDL_DestroyTexture(m_texture);
    }
    SDL_RenderPresent(m_renderer);
    return (false);
}

int rand_range(int min, int max) { return rand() % (max - min + 1) + min; }

void DisplaySDL::displayGame(const std::vector<std::string> &map,
    const std::map<std::string, std::size_t> &scores, std::size_t score, std::size_t lives)
{
    Arcade::Color color;
    int y_offset = 0;

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    m_surface = IMG_Load(m_title.image.c_str());
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            m_rect.x = (1920 / 2) - ((map[i].size() * 20) / 2) + (j * 20);
            m_rect.y = (1080 / 2) - ((map.size() * 20) / 2) + (i * 20);
            if (m_gamePixel.contains(map[i][j])) {
                if (m_gamePixel[map[i][j]].m) {
                    SDL_SetRenderDrawColor(m_renderer, rand_range(0, 255), rand_range(0, 255),
                        rand_range(0, 255), 255);
                    SDL_RenderFillRect(m_renderer, &m_rect);
                } else {
                    color = m_gamePixel[map[i][j]].c;
                    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
                    SDL_RenderFillRect(m_renderer, &m_rect);
                }
            }
        }
    }
    // display game best score / lives / score
    auto best = std::max_element(
        scores.begin(), scores.end(), [](auto &a, auto &b) { return (a.second < b.second); });

    m_surface = TTF_RenderText_Solid(m_font, "Best Score:", {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {(1920 / 2) - ((static_cast<int>(map[0].size()) * 20) / 2),
        ((1080 / 2) + (static_cast<int>(map.size() / 2) * 20)) + m_surface->h, m_surface->w,
        m_surface->h};
    y_offset = m_textureRect.y + m_surface->h;
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = TTF_RenderText_Solid(
        m_font, (best->first + " " + std::to_string(best->second)).c_str(), {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {(1920 / 2) - ((static_cast<int>(map[0].size()) * 20) / 2),
        y_offset + m_surface->h, m_surface->w, m_surface->h};
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface =
        TTF_RenderText_Solid(m_font, ("Lives: " + std::to_string(lives)).c_str(), {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {(1920 / 2) - (m_surface->w / 2),
        ((1080 / 2) + (static_cast<int>(map.size() / 2) * 20)) + m_surface->h, m_surface->w,
        m_surface->h};
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = TTF_RenderText_Solid(m_font, "Score:", {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {(1920 / 2) + ((static_cast<int>(map[0].size()) * 20) / 2) - m_surface->w,
        ((1080 / 2) + (static_cast<int>(map.size() / 2) * 20)) + m_surface->h, m_surface->w,
        m_surface->h};
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = TTF_RenderText_Solid(m_font, std::to_string(score).c_str(), {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {(1920 / 2) + ((static_cast<int>(map[0].size()) * 20) / 2) - m_surface->w,
        y_offset + m_surface->h, m_surface->w, m_surface->h};
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    SDL_RenderPresent(m_renderer);
}

void DisplaySDL::displayVictory(const std::string username, std::size_t scores)
{
    int y_offset = 0;

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    m_surface = TTF_RenderText_Solid(m_font, "VICTORY", {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {(1920 / 2) - ((m_surface->w * 10) / 2),
        ((1080 / 2) - ((m_surface->h * 10) / 2)) - 100, m_surface->w * 10, m_surface->h * 10};
    y_offset = m_textureRect.y + m_textureRect.h;
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    // display Player name
    m_surface = TTF_RenderText_Solid(m_font, ("Player : " + username).c_str(), {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {
        (1920 / 2) - ((m_surface->w * 2) / 2), y_offset + (m_surface->h * 2), m_surface->w * 2, m_surface->h * 2};
    y_offset = m_textureRect.y + m_textureRect.h;
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);
    // display Player score
    m_surface = TTF_RenderText_Solid(m_font, ("Score : " + std::to_string(scores)).c_str(), {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {
        (1920 / 2) - ((m_surface->w * 2) / 2), y_offset + m_surface->h, m_surface->w * 2, m_surface->h * 2};
    y_offset = m_textureRect.y + m_textureRect.h;
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);
    // display "Press ESC to quit or ENTER to restart"
    m_surface = TTF_RenderText_Solid(m_font, "Press ESC to quit or ENTER to restart", {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {
        (1920 / 2) - ((m_surface->w * 2) / 2), y_offset + (m_surface->h * 2), m_surface->w * 2, m_surface->h * 2};
    y_offset = m_textureRect.y + m_textureRect.h;
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);
    SDL_RenderPresent(m_renderer);
}

void DisplaySDL::displayGameover(const std::string username, std::size_t scores)
{
    int y_offset = 0;

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    m_surface = TTF_RenderText_Solid(m_font, "GAME OVER", {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {(1920 / 2) - ((m_surface->w * 10) / 2),
        ((1080 / 2) - ((m_surface->h * 10) / 2)) - 100, m_surface->w * 10, m_surface->h * 10};
    y_offset = m_textureRect.y + m_textureRect.h;
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    // display Player name
    m_surface = TTF_RenderText_Solid(m_font, ("Player : " + username).c_str(), {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {
        (1920 / 2) - ((m_surface->w * 2) / 2), y_offset + (m_surface->h * 2), m_surface->w * 2, m_surface->h * 2};
    y_offset = m_textureRect.y + m_textureRect.h;
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);
    // display Player score
    m_surface = TTF_RenderText_Solid(m_font, ("Score : " + std::to_string(scores)).c_str(), {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {
        (1920 / 2) - ((m_surface->w * 2) / 2), y_offset + m_surface->h, m_surface->w * 2, m_surface->h * 2};
    y_offset = m_textureRect.y + m_textureRect.h;
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);
    // display "Press ESC to quit or ENTER to restart"
    m_surface = TTF_RenderText_Solid(m_font, "Press ESC to quit or ENTER to restart", {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    m_textureRect = {
        (1920 / 2) - ((m_surface->w * 2) / 2), y_offset + (m_surface->h * 2), m_surface->w * 2, m_surface->h * 2};
    y_offset = m_textureRect.y + m_textureRect.h;
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textureRect);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);
    SDL_RenderPresent(m_renderer);
}

Arcade::KeyboardInput DisplaySDL::getInput()
{
    SDL_Event event;
    using Key = Arcade::KeyboardInput::Key;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RETURN:
                    return (Arcade::KeyboardInput(Key::ENTER, event.key.keysym.sym));
                case SDLK_e:
                    return (Arcade::KeyboardInput(Key::E, event.key.keysym.sym));
                case SDLK_z:
                    return (Arcade::KeyboardInput(Key::Z, event.key.keysym.sym));
                case SDLK_q:
                    return (Arcade::KeyboardInput(Key::Q, event.key.keysym.sym));
                case SDLK_s:
                    return (Arcade::KeyboardInput(Key::S, event.key.keysym.sym));
                case SDLK_d:
                    return (Arcade::KeyboardInput(Key::D, event.key.keysym.sym));
                case SDLK_p:
                    return (Arcade::KeyboardInput(Key::P, event.key.keysym.sym));
                case SDLK_UP:
                    return (Arcade::KeyboardInput(Key::UP, event.key.keysym.sym));
                case SDLK_DOWN:
                    return (Arcade::KeyboardInput(Key::DOWN, event.key.keysym.sym));
                case SDLK_LEFT:
                    return (Arcade::KeyboardInput(Key::LEFT, event.key.keysym.sym));
                case SDLK_RIGHT:
                    return (Arcade::KeyboardInput(Key::RIGHT, event.key.keysym.sym));
                case SDLK_SPACE:
                    return (Arcade::KeyboardInput(Key::SPACE, event.key.keysym.sym));
                case SDLK_ESCAPE:
                    return (Arcade::KeyboardInput(Key::ESCAPE, event.key.keysym.sym));
                default:
                    return (Arcade::KeyboardInput(Key::NN, event.key.keysym.sym));
            }
        }
    }
    return (Arcade::KeyboardInput(Key::NN, 0));
}

void loadDisplaySDL() { instance = new DisplaySDL; }

void unloadDisplaySDL() { delete instance; }

extern "C" DisplaySDL *entryPoint() { return (instance); }

extern "C" Arcade::ModuleType getType() { return (Arcade::ModuleType::Display); }
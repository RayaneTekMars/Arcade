/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** DisplaySDL
*/

#pragma once

#include "ADisplayModule.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class DisplaySDL : Arcade::ADisplayModule
{

    public:

        DisplaySDL();
        ~DisplaySDL() final;

        void init() final;
        void initGame(const Title &title, const std::map<char, Arcade::Pixel> &subPixel) final;

        void stop() final;

        bool displayMainMenu(const Arcade::KeyboardInput &key,
            const std::vector<Arcade::IDisplayModule *> &libs,
            const std::vector<Arcade::IGameModule *> &games, std::string &username,
            int &choice) final;
        void displayGame(const std::vector<std::string> &map,
            const std::map<std::string, std::size_t> &scores, std::size_t score,
            std::size_t lives) final;
        void displayVictory(const std::string username, std::size_t scores) final;
        void displayGameover(const std::string username, std::size_t scores) final;

        Arcade::KeyboardInput getInput() final;

    private:

        bool m_enter;

        SDL_Rect m_rect;
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

        TTF_Font *m_font;
        SDL_Surface *m_surface;
        SDL_Texture *m_texture;
        SDL_Rect m_textureRect;
};

void loadDisplaySDL() __attribute__((constructor));

void unloadDisplaySDL() __attribute__((destructor));

extern "C" DisplaySDL *entryPoint();

extern "C" Arcade::ModuleType getType();
/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** Core
*/

#pragma once

#include "DLLoader.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

#include <exception>
#include <filesystem>
#include <memory>
#include <regex>
#include <string>
#include <unistd.h>
#include <vector>
#include <chrono>

namespace fs = std::filesystem;

namespace Arcade
{
    /**
     * @class Core
     * @brief Class for the arcade core
     */
    class Core
    {
        public:

            class Exception : std::exception
            {
                public:

                    Exception(const std::string &message);
                    virtual ~Exception();

                    const char *what() const noexcept;

                private:

                    std::string m_message;
            };

            class UsageException : public Exception
            {
                public:

                    UsageException();
                    ~UsageException();
            };

        public:

            /**
             * @brief Constructor
             */
            Core();

            /**
             * @brief Destructor
             */
            ~Core();

            /**
             * @brief initialize arcade core
             */
            void init(int ac, char **av);

            /**
             * @brief main loop of the arcade core
             */
            void loop();

        private:

            /**
             * @brief load the modules
             */
            void loadLibs();

            /**
             * @brief display modules swapping
             */
            void swapDisplays();

            /**
             * @brief game modules swapping
             */
            void swapGames();

            /**
             * @brief game loop
             */
            void loopGame();

            /**
             * @brief meun loop
             */
            void loopMenu();

            static const std::string m_usage;

            std::vector<std::unique_ptr<Arcade::DLLoader>> m_dll;
            std::vector<IDisplayModule *> m_dispMod;
            std::vector<IGameModule *> m_gameMod;
            Arcade::KeyboardInput m_key;
            std::string m_username;
            fs::path m_libinit;
            bool m_menu, m_open;
            int m_gameChoice;
            int m_libChoice;
    };
} // namespace Arcade
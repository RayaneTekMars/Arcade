/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** IDisplayModule
*/

/**
 * @file IDisplayModule.hpp
 * @brief Display module interface
 *
 * @authors Yasmine Boussadia
 * @authors Rayane Eloudjedi
 * @authors Bitoune Kyrian
 *
 * Interface for graphic libraries
 */

#pragma once

#include "IGameModule.hpp"
#include "KeyboardInput.hpp"
#include "ModuleType.hpp"
#include "Pixel.hpp"
#include "Title.hpp"

#include <map>
#include <string>
#include <vector>

/**
 * @namespace Arcade
 * @brief Arcade namespace
 */
namespace Arcade
{
    /**
     * @class IDisplayModule
     * @brief Interface for graphic libraries
     */
    class IDisplayModule
    {
        public:

            /**
             * @brief Virtual destructor
             */
            virtual ~IDisplayModule() = default;

            /**
             * @brief init the display module
             */
            virtual void init() = 0;

            /**
             * @brief init the display module for the game
             */
            virtual void initGame(const Title &title, const std::map<char, Pixel> &subPixel) = 0;

            /**
             * @brief stop the display module
             */
            virtual void stop() = 0;

            /**
             * @brief update the main menu display
             *
             * @param key keyboard input from the user
             * @param libs displays modules available
             * @param games games modules available
             * @param username user name
             * @param choice the game module choose
             * @return true if the game start
             * @return false if the game not
             */
            virtual bool displayMainMenu(const Arcade::KeyboardInput &key,
                const std::vector<Arcade::IDisplayModule *> &libs,
                const std::vector<Arcade::IGameModule *> &games, std::string &username,
                int &choice) = 0;

            /**
             * @brief update the game display
             *
             * @param map time map from the game
             * @param scores LeaderBoard from the game
             * @param score current score from the game
             * @param lives current lives from the game
             */
            virtual void displayGame(const std::vector<std::string> &map,
                const std::map<std::string, std::size_t> &scores, std::size_t score,
                std::size_t lives) = 0;

            /**
             * @brief update the victory display
             *
             * @param username user name
             * @param scores score from the game
             */
            virtual void displayVictory(const std::string username, std::size_t scores) = 0;

            /**
             * @brief update the game over display
             *
             * @param username user name
             * @param scores score from the game
             */
            virtual void displayGameover(const std::string username, std::size_t scores) = 0;

            /**
             * @brief Get the Name of the display module
             *
             * @return const std::string& display module name
             */
            virtual const std::string &getName() = 0;

            /**
             * @brief Get the Input from the display module
             *
             * @return KeyboardInput user input
             */
            virtual KeyboardInput getInput() = 0;
    };
} // namespace Arcade

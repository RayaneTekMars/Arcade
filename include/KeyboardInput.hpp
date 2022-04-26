/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** KeyboardInput
*/

#pragma once

namespace Arcade
{

    /**
     * @class KeyboardInput
     * @brief Keyboard input class
     */
    struct KeyboardInput
    {
        public:

            /**
             * @enum Key
             * @brief Key enum class that encapsulate native key enum from graphics library
             */
            enum class Key {
                NN = -1,
                ENTER,
                E,
                Z,
                Q,
                S,
                D,
                P,
                R,
                UP,
                DOWN,
                LEFT,
                RIGHT,
                SPACE,
                ESCAPE
            };

            /**
             * @brief Constructor
             * @param key the key
             * @param code native code from the graphics library
             */
            KeyboardInput(Key _key, int _code) : key(_key), code(_code) {}

            /**
             * @brief Default Constructor
             */
            KeyboardInput() = default;

            /**
             * @brief Default destructor
             */
            ~KeyboardInput() = default;

            Key key = Key::NN;
            int code = -1;
    };
} // namespace Arcade
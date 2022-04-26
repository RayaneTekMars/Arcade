/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Title
*/

#pragma once

#include <string>
#include <vector>
#include <fstream>

struct Title
{
    public:

        Title(const std::string &imagePath, const std::string &asciiPath)
        {
            std::ifstream file(asciiPath);
            std::string buffer;

            image = imagePath;
            if (file.is_open()) {
                while (std::getline(file, buffer, '\n'))
                    ascii.push_back(std::move(buffer));
            }
        }

        Title() = default;

        ~Title() = default;

        std::vector<std::string> ascii;
        std::string image;
};
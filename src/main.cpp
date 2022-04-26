/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** main
*/

#include "Core.hpp"

int main(int ac, char **av)
{
    Arcade::Core core;

    try {
        core.init(ac, av);
        core.loop();
    } catch (const Arcade::Core::UsageException &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    } catch (const Arcade::Core::Exception &e) {
        std::cerr << av[0] << ": " << e.what() << std::endl;
        return (84);
    } catch (...) {
        std::cerr << av[0] << ": unknown error" << std::endl;
        return (84);
    }
    return (0);
}

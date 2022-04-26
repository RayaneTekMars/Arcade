# Arcade
Arcade is a gaming platform, a program that lets the user choose a game to play and keeps a register of player scores.

## Requirements

`Build`
- C++20 compiler
- cmake 3.17

`Libraries`
- SFML
- SDL
- NCURSES
- NCURSESW

## Build

```
mkdir build && cd build
cmake ..
cmake --build .
```

## Librairies
### Graphic
We include `3` graphic libs:   
- SFML
- SDL
- NCURSES   

### Game
We include `2` game libs:
- Nibbler
- Pacman  

## Usage
```bash
USAGE:
  ./arcade path_to_graphical_lib
  
DESCRIPTION:
  lib         path to the initial graphical library to load (./lib/arcade_lib_name.so)
  
COMMANDS:
  RIGHT ARROW   next graphic lib
  LEFT ARROW    previous graphic lib
  UP ARROW      next game lib
  DOWN ARROW    previous game lib

  ENTER       restart the game (only available when game finish)
  ESC         quit arcade or return to menu
  
  D     move right
  Q     move left
  Z     move up
  S     move down
```

## Documentation

[![doc](https://img.shields.io/badge/Documentation-pdf-red.svg)](./doc/documentation.pdf)

## Contributors

- [Kyrian BITOUNE](https://github.com/kbitoune)
- [Yasmine BOUSSADIA](https://github.com/yboussadia)
- [Rayane ELOUDJEDI](https://github.com/RayaneTekMars)
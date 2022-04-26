file(GLOB PACMAN_SOURCES "../*.cpp" "./src/*.cpp")

include_directories(
    ./include
    ${ARCADE_SOURCE_DIR}/include
)

add_library(arcade_pacman SHARED ${PACMAN_SOURCES})

set_target_properties(arcade_pacman PROPERTIES PREFIX "")
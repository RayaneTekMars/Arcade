file(GLOB SOURCES_SDL2 "../*.cpp" "src/*.cpp")

include_directories(
    ./include
    ${ARCADE_SOURCE_DIR}/include
)

add_library(arcade_sdl2 SHARED ${SOURCES_SDL2})

target_link_libraries(arcade_sdl2 PRIVATE
    SDL2
    SDL2_image
    SDL2_mixer
    SDL2_ttf
)

set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")

file(GLOB SOURCES_SFML "../*.cpp" "src/*.cpp")

include_directories(
    ./include
    ${ARCADE_SOURCE_DIR}/include
)

add_library(arcade_sfml SHARED ${SOURCES_SFML})

target_link_libraries(arcade_sfml PRIVATE
    sfml-audio
    sfml-graphics
    sfml-network
    sfml-system
    sfml-window
)

set_target_properties(arcade_sfml PROPERTIES PREFIX "")
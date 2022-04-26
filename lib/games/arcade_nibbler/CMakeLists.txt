file(GLOB NIBBLER_SOURCES "../*.cpp" "./src/*.cpp")

include_directories(
    ./include
    ${ARCADE_SOURCE_DIR}/include
)

add_library(arcade_nibbler SHARED ${NIBBLER_SOURCES})

set_target_properties(arcade_nibbler PROPERTIES PREFIX "")
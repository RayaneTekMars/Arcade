set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

include(FindCurses)

find_package(Curses REQUIRED)

file(GLOB SOURCES_NCURSES "../*.cpp" "src/*.cpp")

include_directories(
    include
    ${CURSES_INCLUDE_DIRS}
    ${ARCADE_SOURCE_DIR}/include
)

add_library(arcade_ncurses SHARED ${SOURCES_NCURSES})

target_link_libraries(arcade_ncurses ${CURSES_LIBRARIES})

set_target_properties(arcade_ncurses PROPERTIES PREFIX "")
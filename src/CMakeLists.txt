include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "*.cpp" "*/*.cpp")

add_executable(arcade ${SOURCES})

target_link_libraries(arcade ${CMAKE_DL_LIBS})
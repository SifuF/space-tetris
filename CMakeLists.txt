cmake_minimum_required(VERSION 3.28)

project(Tetris VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory("${CMAKE_SOURCE_DIR}/submodules/SFML")

option(GRAPHICS "Enable Graphics mode" ON)
configure_file(TetrisConfig.h.in TetrisConfig.h)

set(HEADERS
    src/Background.h
    src/GameConfig.h
    src/Grid.h
    src/Keys.h
    src/Manager.h
    src/Sound.h
    src/Tetromino.h
    src/Text.h
    src/Timer.h
)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_BINARY_DIR}"
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    sfml-graphics
    sfml-system
    sfml-window
    sfml-network
    sfml-audio
)

file(COPY ${PROJECT_SOURCE_DIR}/data/ DESTINATION ${PROJECT_BINARY_DIR}/data/)
file(COPY ${PROJECT_SOURCE_DIR}/fonts/ DESTINATION ${PROJECT_BINARY_DIR}/fonts/)
file(COPY ${PROJECT_SOURCE_DIR}/gfx/ DESTINATION ${PROJECT_BINARY_DIR}/gfx/)
file(COPY ${PROJECT_SOURCE_DIR}/sound/ DESTINATION ${PROJECT_BINARY_DIR}/sound/)
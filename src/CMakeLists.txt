cmake_minimum_required(VERSION 3.22.1)

project(Tetris VERSION 1.0)

#set(MAKE_BUILD_TYPE Debug ... FORCE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(GRAPHICS "Enable Graphics mode" ON)
configure_file(TetrisConfig.h.in TetrisConfig.h)

add_executable(Tetris main.cpp)

if(WIN32)
set_target_properties(Tetris PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
endif() 

target_include_directories(Tetris PUBLIC
    "${PROJECT_BINARY_DIR}"
)

if(WIN32)
target_include_directories(Tetris PUBLIC
    "${PROJECT_SOURCE_DIR}/SFML/include"
)

target_link_directories(Tetris PUBLIC
    "${PROJECT_SOURCE_DIR}/SFML/lib"
)
endif() 

target_link_libraries(Tetris PUBLIC
    optimized sfml-graphics
    optimized sfml-system
    optimized sfml-window
    optimized sfml-network
    optimized sfml-audio
)

if(WIN32)
target_link_libraries(Tetris PUBLIC
    debug sfml-main-d optimized sfml-main
    debug sfml-graphics-d
    debug sfml-system-d
    debug sfml-window-d
    debug sfml-network-d
    debug sfml-audio-d
)
endif() 

configure_file("${PROJECT_SOURCE_DIR}/arial.ttf" "${PROJECT_BINARY_DIR}/arial.ttf" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/data.txt" "${PROJECT_BINARY_DIR}/data.txt" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/data2.txt" "${PROJECT_BINARY_DIR}/data2.txt" COPYONLY)
file(COPY ${PROJECT_SOURCE_DIR}/sound/ DESTINATION ${PROJECT_BINARY_DIR}/sound/)
file(COPY ${PROJECT_SOURCE_DIR}/gfx/ DESTINATION ${PROJECT_BINARY_DIR}/gfx/)
if(WIN32)
file(COPY ${PROJECT_SOURCE_DIR}/SFML/dll/ DESTINATION ${PROJECT_BINARY_DIR})
endif() 

#install(TARGETS Tetris DESTINATION bin)
#install(FILES "${PROJECT_SOURCE_DIR}/arial.ttf" DESTINATION bin)
#install(FILES "${PROJECT_SOURCE_DIR}/data.txt" DESTINATION bin)
#install(FILES "${PROJECT_SOURCE_DIR}/data2.txt" DESTINATION bin)
#install(DIRECTORY "${PROJECT_SOURCE_DIR}/sound/" DESTINATION bin/sound)
#install(DIRECTORY "${PROJECT_SOURCE_DIR}/gfx/" DESTINATION bin/gfx)
#if(WIN32)
#install(DIRECTORY "${PROJECT_SOURCE_DIR}/SFML/dll/" DESTINATION bin)
#endif()


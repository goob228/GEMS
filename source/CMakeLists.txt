cmake_minimum_required(VERSION 3.10)
project(GEMS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.1 COMPONENTS Graphics Window System REQUIRED)

add_executable(GEMS
    main.cpp
    Gem.cpp
    window.cpp
    Game.cpp

    Gem.h
    window.h
    Game.h
)

target_include_directories(GEMS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GEMS
    SFML::Graphics
    SFML::Window
    SFML::System
)
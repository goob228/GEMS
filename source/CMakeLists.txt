cmake_minimum_required(VERSION 3.10)
project(GEMS VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)


find_package(SFML 2.6 COMPONENTS system window graphics audio network REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(GEMS ${SRC_FILES})



target_link_libraries(GEMS 
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
)


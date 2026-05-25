cmake_minimum_required(VERSION 3.10)
project(GEMS VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.6.2")

include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(${SFML_DIR}/include)

link_directories(${SFML_DIR}/lib)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(GEMS ${SRC_FILES})



target_link_libraries(GEMS 
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
)


if(WIN32)

    set(SFML_BIN_DIR "${SFML_DIR}/bin")
    set(TARGET_DIR "$<TARGET_FILE_DIR:GEMS>")

    set(SFML_DLLS
        sfml-system-2.dll
        sfml-window-2.dll
        sfml-graphics-2.dll
        sfml-audio-2.dll
        sfml-network-2.dll
        openal32.dll         
    )

    foreach(DLL ${SFML_DLLS})
        add_custom_command(TARGET GEMS POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SFML_BIN_DIR}/${DLL}"
                "${TARGET_DIR}"
            COMMENT "Copying ${DLL} in ${TARGET_DIR}"
        )
    endforeach()
endif()
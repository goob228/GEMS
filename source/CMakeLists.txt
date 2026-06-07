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

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        if(MINGW)
            get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

            # Список файлов для копирования
            set(MINGW_DLLS 
                libgcc_s_seh-1.dll
                libstdc++-6.dll 
                libwinpthread-1.dll
            )
            foreach(DLL ${MINGW_DLLS})
                file(COPY "${MINGW_BIN_DIR}/${DLL}"
                    DESTINATION "${CMAKE_BINARY_DIR}")
            endforeach()
        endif()
    endif()

endif()
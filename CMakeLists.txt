cmake_minimum_required(VERSION 2.8)
if(POLICY CMP0040)
  cmake_policy(SET CMP0040 OLD)
endif()

PROJECT(sdl_audio)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP8 -std:c++17")
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
    add_definitions( -Wall -Wno-sign-compare)
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/SDL2-2.0.8_prebuilt_windows/include)

link_directories(${CMAKE_CURRENT_LIST_DIR}/SDL2-2.0.8_prebuilt_windows/x64/Debug/)


add_executable(sdl_audio
    main.cpp
    sdl_audio.cpp
    sdl_audio.h
    setup.h
    )
target_link_libraries(sdl_audio
    WINMM.LIB
    version.lib
    Imm32.lib
    SDL2.lib
    SDL2main.lib
)

install(TARGETS ${module_id} DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT sdl_audio)


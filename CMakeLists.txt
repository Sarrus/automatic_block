cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(automatic_block C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(automatic_block main.c)

target_include_directories(automatic_block PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(automatic_block PUBLIC pico_stdlib)

pico_add_extra_outputs(automatic_block)
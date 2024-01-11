cmake_minimum_required(VERSION 3.12.1)

project(stb LANGUAGES CXX)

set(_STB_DIR ${CMAKE_CURRENT_SOURCE_DIR}) 

add_library(
    ${PROJECT_NAME} STATIC
        ${_STB_DIR}/stb_image.h
        ${_STB_DIR}/stb_image.cpp
)

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC 
            ${_STB_DIR}
)

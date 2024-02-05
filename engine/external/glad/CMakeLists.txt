cmake_minimum_required(VERSION 3.12.1)

project(glad)

set(_GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}) 

add_library(
    ${PROJECT_NAME} STATIC
       ${_GLAD_DIR}/include/glad/glad.h
       ${_GLAD_DIR}/include/KHR/khrplatform.h
       ${_GLAD_DIR}/src/glad.c
)

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC 
            ${_GLAD_DIR}/include
)

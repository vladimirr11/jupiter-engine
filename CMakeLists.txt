cmake_minimum_required(VERSION 3.12.1)

project(JupiterApp LANGUAGES CXX)

set(_JUPITER_ENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/jupiter) 
set(_JUPITER_APP2D_DIR ${CMAKE_CURRENT_SOURCE_DIR}/playground/2dsandbox) 
set(_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build) 

add_executable(
    ${PROJECT_NAME} 
        ${_JUPITER_APP2D_DIR}/JupiterApp2d.cpp
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /std:c++20)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -std=c++20)
endif()

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE 
            jupiter
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:jupiter>              
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

add_subdirectory(${_JUPITER_ENGINE_DIR})

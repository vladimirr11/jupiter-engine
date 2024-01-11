cmake_minimum_required(VERSION 3.12.1)

project(JupiterApp LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(_JUPITER_ENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/jupiter) 
set(_JUPITER_APP2D_DIR ${CMAKE_CURRENT_SOURCE_DIR}/playground/2dsandbox) 
set(_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build) 

add_executable(
    ${PROJECT_NAME} 
        ${_JUPITER_APP2D_DIR}/JupiterApp2d.cpp
)

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
    ${_JUPITER_APP2D_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

add_subdirectory(${_JUPITER_ENGINE_DIR})

cmake_minimum_required(VERSION 3.12.1)

project(jupiter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(_EXTERNAL_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external_libs) 
set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include) 
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src) 

add_library(
    ${PROJECT_NAME} SHARED
        # Include
        ${_INC_DIR}/jupiter/base/Application.h
        ${_INC_DIR}/jupiter/base/BaseDefines.h
        ${_INC_DIR}/jupiter/base/EntryPoint.h
        ${_INC_DIR}/jupiter/base/Logger.h

        ${_INC_DIR}/jupiter/events/Event.h
        ${_INC_DIR}/jupiter/events/EventDefines.h
        ${_INC_DIR}/jupiter/events/EventHandler.h
        ${_INC_DIR}/jupiter/events/EventManager.h
        ${_INC_DIR}/jupiter/events/KeyboardEvents.h
        ${_INC_DIR}/jupiter/events/MouseEvents.h
        ${_INC_DIR}/jupiter/events/WindowEvents.h

        ${_INC_DIR}/jupiter/Jpch.h
        ${_INC_DIR}/jupiter/Jupiter.h

        # Source
        ${_SRC_DIR}/base/Application.cpp
        ${_SRC_DIR}/base/Logger.cpp

        ${_SRC_DIR}/events/EventManager.cpp

        ${_SRC_DIR}/Jpch.cpp
)

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC   
       # Prevents Windows.h from adding unnecessary includes    
       WIN32_LEAN_AND_MEAN  
       # Prevents Windows.h from defining min/max as macros 
       NOMINMAX 
       # Jupiter specific defines
       JUPITER_PLATFORM_WINDOWS
       JUPITER_BUILD_DLL
    )   
endif()

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC 
            ${_INC_DIR}
            ${_EXTERNAL_LIBS_DIR}/fmt/include
)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE 
            fmt
)

add_subdirectory(${_EXTERNAL_LIBS_DIR}/fmt)

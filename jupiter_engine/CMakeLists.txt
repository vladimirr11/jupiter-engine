cmake_minimum_required(VERSION 3.12.1)

project(jupiter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(_EXTERNAL_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external) 
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src) 

# disable building glfw docs, testx, and examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_library(
    ${PROJECT_NAME} STATIC
       
        ${_SRC_DIR}/base/Application.h
        ${_SRC_DIR}/base/Application.cpp
        ${_SRC_DIR}/base/Assert.h
        ${_SRC_DIR}/base/BaseDefines.h
        ${_SRC_DIR}/base/EntryPoint.h
        ${_SRC_DIR}/base/Input.h
        ${_SRC_DIR}/base/Logger.h
        ${_SRC_DIR}/base/Window.h
          
        ${_SRC_DIR}/events/Event.h
        ${_SRC_DIR}/events/EventDefines.h
        ${_SRC_DIR}/events/EventHandler.h
        ${_SRC_DIR}/events/EventManager.h
        ${_SRC_DIR}/events/EventManager.cpp
        ${_SRC_DIR}/events/KeyboardEvents.h
        ${_SRC_DIR}/events/MouseEvents.h
        ${_SRC_DIR}/events/WindowEvents.h

        ${_SRC_DIR}/math/matrix/Matrix4x4.h
        ${_SRC_DIR}/math/matrix/Transform.h
        ${_SRC_DIR}/math/vector/Vector.h
        ${_SRC_DIR}/math/vector/Vector2.h
        ${_SRC_DIR}/math/vector/Vector3.h
        ${_SRC_DIR}/math/vector/Vector4.h
        ${_SRC_DIR}/math/MathUtils.h
        
        ${_SRC_DIR}/memory/LinearAllocator.h
        ${_SRC_DIR}/memory/LinearAllocator.cpp
        ${_SRC_DIR}/memory/Memory.h

        ${_SRC_DIR}/platform/win32/Win32Input.cpp
        ${_SRC_DIR}/platform/win32/Win32Window.h
        ${_SRC_DIR}/platform/win32/Win32Window.cpp

        ${_SRC_DIR}/ui/imgui/ImGuiUILayer.h
        ${_SRC_DIR}/ui/imgui/ImGuiUILayer.cpp
        ${_SRC_DIR}/ui/UILayer.h

        ${_SRC_DIR}/Jupiter.h
        ${_SRC_DIR}/Jpch.h
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
    )   

    # enable warnings
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /W3)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
    endif()
endif()

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC 
            ${_SRC_DIR}
            ${_EXTERNAL_LIBS_DIR}/fmt/include
            ${_EXTERNAL_LIBS_DIR}/glfw/include
            ${_EXTERNAL_LIBS_DIR}/glad/include
            ${_EXTERNAL_LIBS_DIR}/imgui
)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE 
            fmt
            glfw
            glad
            imgui
)

add_subdirectory(${_EXTERNAL_LIBS_DIR}/fmt)
add_subdirectory(${_EXTERNAL_LIBS_DIR}/glfw)
add_subdirectory(${_EXTERNAL_LIBS_DIR}/glad)
add_subdirectory(${_EXTERNAL_LIBS_DIR}/imgui)

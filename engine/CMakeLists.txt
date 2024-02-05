cmake_minimum_required(VERSION 3.12.1)

project(jupiter LANGUAGES CXX)

set(_EXTERNAL_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external) 
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src) 

# disable building glfw docs, testx, and examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# enable/disable Tracy profiling
set(TRACY_ENABLE ON)

add_library(
    ${PROJECT_NAME} STATIC
       
        ${_SRC_DIR}/base/Application.h
        ${_SRC_DIR}/base/Application.cpp
        ${_SRC_DIR}/base/Assert.h
        ${_SRC_DIR}/base/Defines.h
        ${_SRC_DIR}/base/Entry.h
        ${_SRC_DIR}/base/Input.cpp
        ${_SRC_DIR}/base/Input.h
        ${_SRC_DIR}/base/Logger.h
        ${_SRC_DIR}/base/Profile.h
        ${_SRC_DIR}/base/Random.h
        ${_SRC_DIR}/base/Timer.h
        ${_SRC_DIR}/base/Window.cpp
        ${_SRC_DIR}/base/Window.h

        ${_SRC_DIR}/cameras/BaseCamera.h
        ${_SRC_DIR}/cameras/OrthographicCamera.cpp
        ${_SRC_DIR}/cameras/OrthographicCamera.h
        ${_SRC_DIR}/cameras/PrespectiveCamera.cpp
        ${_SRC_DIR}/cameras/PrespectiveCamera.h
          
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
        
        ${_SRC_DIR}/memory/MemoryArena.h
        ${_SRC_DIR}/memory/MemoryArena.cpp
        ${_SRC_DIR}/memory/MemoryUtils.h

        ${_SRC_DIR}/renderer/opengl/GLAssert.h
        ${_SRC_DIR}/renderer/opengl/GLContext.cpp
        ${_SRC_DIR}/renderer/opengl/GLContext.h
        ${_SRC_DIR}/renderer/opengl/GLIndexBuffer.cpp
        ${_SRC_DIR}/renderer/opengl/GLIndexBuffer.h
        ${_SRC_DIR}/renderer/opengl/GLRenderer.cpp
        ${_SRC_DIR}/renderer/opengl/GLRenderer.h
        ${_SRC_DIR}/renderer/opengl/GLShader.cpp
        ${_SRC_DIR}/renderer/opengl/GLShader.h
        ${_SRC_DIR}/renderer/opengl/GLTexture.cpp
        ${_SRC_DIR}/renderer/opengl/GLTexture.h
        ${_SRC_DIR}/renderer/opengl/GLVertexArray.cpp
        ${_SRC_DIR}/renderer/opengl/GLVertexArray.h
        ${_SRC_DIR}/renderer/opengl/GLVertexBuffer.cpp
        ${_SRC_DIR}/renderer/opengl/GLVertexBuffer.h

        ${_SRC_DIR}/renderer/GraphicsContext.h
        ${_SRC_DIR}/renderer/IndexBuffer.cpp
        ${_SRC_DIR}/renderer/IndexBuffer.h
        ${_SRC_DIR}/renderer/BatchRenderer.cpp
        ${_SRC_DIR}/renderer/BatchRenderer.h
        ${_SRC_DIR}/renderer/Renderer.h
        ${_SRC_DIR}/renderer/RendererBackend.cpp
        ${_SRC_DIR}/renderer/RendererBackend.h
        ${_SRC_DIR}/renderer/Shader.cpp
        ${_SRC_DIR}/renderer/Shader.h
        ${_SRC_DIR}/renderer/Texture.cpp
        ${_SRC_DIR}/renderer/Texture.h
        ${_SRC_DIR}/renderer/VertexArray.cpp
        ${_SRC_DIR}/renderer/VertexArray.h
        ${_SRC_DIR}/renderer/VertexBuffer.cpp
        ${_SRC_DIR}/renderer/VertexBuffer.h

        ${_SRC_DIR}/resources/ShaderLoader.cpp
        ${_SRC_DIR}/resources/ShaderLoader.h
        ${_SRC_DIR}/resources/TextureLoader.cpp
        ${_SRC_DIR}/resources/TextureLoader.h

        ${_SRC_DIR}/scene/primitives/2DPrimitives.h

        ${_SRC_DIR}/ui/imgui/ImGuiUILayer.h
        ${_SRC_DIR}/ui/imgui/ImGuiUILayer.cpp
        ${_SRC_DIR}/ui/UILayer.h

        ${_SRC_DIR}/Jupiter.h
        ${_SRC_DIR}/Jpch.h
        ${_SRC_DIR}/Jpch.cpp
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /std:c++20)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -std=c++2a -march=native)
endif()

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC 
            ${_SRC_DIR}
            ${_EXTERNAL_LIBS_DIR}/fmt/include
            ${_EXTERNAL_LIBS_DIR}/glfw/include
            ${_EXTERNAL_LIBS_DIR}/glad/include
            ${_EXTERNAL_LIBS_DIR}/imgui
            ${_EXTERNAL_LIBS_DIR}/stb
            ${_EXTERNAL_LIBS_DIR}/tracy
)

add_subdirectory(${_EXTERNAL_LIBS_DIR}/fmt)
add_subdirectory(${_EXTERNAL_LIBS_DIR}/glfw)
add_subdirectory(${_EXTERNAL_LIBS_DIR}/glad)
add_subdirectory(${_EXTERNAL_LIBS_DIR}/imgui)
add_subdirectory(${_EXTERNAL_LIBS_DIR}/stb)
add_subdirectory(${_EXTERNAL_LIBS_DIR}/tracy)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE 
            fmt
            glfw
            glad
            imgui
            stb
            Tracy::TracyClient
)
